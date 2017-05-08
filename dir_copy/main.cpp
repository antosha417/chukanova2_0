#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstdio>
#include <vector>
#include <thread>
#include <mutex>
#include <cstring>
#include <iostream>
#include <queue>
#include <atomic>
#include <fstream>

class file{
 public:
  dirent *dir;
  char* path;
  file(dirent *dir, char*);
  file(dirent *dir, char*, char*);
  ~file();
};

file::file(dirent *dir_, char* path_) {
  dir = new dirent;
  path = new char [1000];
  dir->d_type = dir_->d_type;
  strcpy(dir->d_name, dir_->d_name);
  strcpy(path, path_);
}

file::file(dirent *dir_, char* path_, char* name_) {
  dir = new dirent;
  path = new char [1000];
  dir->d_type = dir_->d_type;
  strcpy(dir->d_name, dir_->d_name);
  strcpy(path, path_);
  strcat(path, "/");
  strcat(path, name_);
}

file::~file(){
  delete dir;
  delete path;
}

class Copy{
 public:
  Copy(char*, char*, unsigned);

 private:
  unsigned n;
  char * from;
  char * to;
  int files_amount;
  std::atomic<unsigned > done;

  std::vector<std::queue<file*>> queues;
  std::vector<std::mutex> mtxs;
  std::vector<std::thread> workers;

  void copy(int);
  void create_dir(char*);
  bool dir_exists(char *);
  static void copy_file(char*, char*);
  static int count_all_files(char* name);
  static int count_files(char* name, std::queue<file*>& dirs);

  file* walk(int number);
};

Copy::Copy(char * from_, char * to_, unsigned n):from(from_), to(to_), queues(n), mtxs(n), n(n) {
  files_amount = count_all_files(from);

  create_dir(to_);

  DIR *d;
  struct dirent *dir;

  d = opendir(from);

  while ((dir = readdir(d)) != NULL) {
    if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
      continue;

    file* f = new file(dir, dir->d_name);
    std::unique_lock<std::mutex> mut(mtxs[0]);
    queues[0].push(f);
    mut.unlock();
  }
  closedir(d);

  for (int i = 0; i < n; ++i) {
    workers.push_back(std::thread([this, i](){copy(i);}));
  }

  for (int i = 0; i < n; ++i) {
    workers[i].join();
  }

}

void Copy::create_dir(char* name) {
  if (!dir_exists(name))
    mkdir(name, 0700);
}

bool Copy::dir_exists(char *name) {
  struct stat st = {0};
  return stat(name, &st) != -1;
}

void Copy::copy(int i) {
  while (done.load() < files_amount) {
    std::unique_lock<std::mutex> m(mtxs[i]);
    file* curr_file = nullptr;

    if (!queues[i].empty()) {
      curr_file = queues[i].front();
      queues[i].pop();
      m.unlock();
    } else {
      m.unlock();
      curr_file = walk(i);
    }
    if (curr_file == nullptr) {
      continue;
    }

    if (curr_file->dir->d_type == DT_REG) {
      char f_name[1000];
      strcpy(f_name, from);
      strcat(f_name, curr_file->path);

      char t_name[1000];
      strcpy(t_name, to);
      strcat(t_name, curr_file->path);

      std::cout<<i<<" Copy file:"<<std::endl;
      std::cout<<f_name<<std::endl<<t_name<<std::endl<<std::endl;

      copy_file(f_name, t_name);

      delete curr_file;
      done.fetch_add(1);

    } else if (curr_file->dir->d_type == DT_DIR) {
      char name[1000];
      strcpy(name, to);
      strcat(name, "/");
      strcat(name, curr_file->path);

      create_dir(name);

      char f_name[1000];
      strcpy(f_name, from);
      strcat(f_name, "/");
      strcat(f_name, curr_file->path);

      DIR *d;
      struct dirent *dir;

      d = opendir(f_name);

      while ((dir = readdir(d)) != NULL) {
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
          continue;

        file* f = new file(dir, curr_file->path, dir->d_name);

        std::unique_lock<std::mutex> mut(mtxs[i]);
        queues[i].push(f);
        mut.unlock();
      }
      closedir(d);
      delete curr_file;
      done.fetch_add(1);
    }
  }
}


int Copy::count_files(char* name, std::queue<file*>& dirs) {
  DIR* d;
  struct dirent *dir;

  d = opendir(name);
  if(!d) return -1;
  int counter = 0;

  while ((dir = readdir(d)) != NULL) {
    if( strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0 )
      counter++;
    else
      continue;

    if (dir->d_type == DT_DIR) {
      file* f = new file(dir, name, dir->d_name);
      dirs.push(f);
    }
  }
  closedir(d);
  return counter;
}

int Copy::count_all_files(char* name){
  std::queue<file*> dirs;
  int counter = count_files(name, dirs);

  while (!dirs.empty()) {

    file* f_temp = dirs.front();
    dirs.pop();
    int temp = count_files(f_temp->path, dirs);
    counter += temp;
    if(temp == -1) {
      counter++;
      std::cout << "Bad!!"<<f_temp->path<<std::endl;
    }
    delete f_temp;
  }
  return counter;
}

file* Copy::walk(int number) {
  for (int i = 0; i < n; i++) {
    if (i == number) {
      continue;
    }
    if (mtxs[i].try_lock()) {
      if (!queues[i].empty()) {
        file* f = queues[i].front();
        queues[i].pop();
        mtxs[i].unlock();
        return f;
      }
      mtxs[i].unlock();
    }
  }
  return nullptr;
}
void Copy::copy_file(char * f_name, char * t_name) {
  std::ifstream  src(f_name, std::ios::binary);
  std::ofstream  dst(t_name,   std::ios::binary);

  dst << src.rdbuf();
}

int main() {
  char from[] = "/home/antosha/Dropbox/programs/school/2.0chukanova/dir_copy/";
  char to[] = "/home/antosha/Dropbox/programs/school/2.0chukanova/test_dir/";

  Copy* a = new Copy(from, to, 1);

  return 0;
}