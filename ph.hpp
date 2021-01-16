#pragma once

namespace ph
{
      namespace file
      {
            extern std::mutex mtx;
      
            
            template <typename To>
            auto read (const char* file) -> To {
                  throw std::runtime_error("not defined");
            }
            
            template <typename From>
            auto write (const char* file, const From& from) -> void {
                  std::lock_guard<std::mutex> lock (mtx);
                  std::ofstream f (file);
                  f << from;
                  f.close();
            }
            
            
      }
}
