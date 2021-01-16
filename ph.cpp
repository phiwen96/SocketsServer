#include "ph.hpp"
using namespace std;



namespace ph::file
{
      mutex mtx;
      
      template <>
      auto read<const char*> (const char* file) -> const char* {
                  lock_guard<mutex> lock (mtx);
            ifstream f (file);
            
            string line, text;
            while (getline(f, line)) {
                  text += line + "\n";
            }
            f.close();
            const char* s = text.c_str();
            return s;
      }
      
      template <>
      auto read<std::string> (const char* file) -> std::string {
            lock_guard<mutex> lock (mtx);
            ifstream f (file);
            
            string line, text;
            while (getline(f, line)) {
                  text += line + "\n";
            }
            f.close();
            return text;
      }
      
      template <>
      auto read<nlohmann::json> (const char* file) -> nlohmann::json {
            return nlohmann::json::parse(read<std::string>(file));
      }
      
//      template <>
//      auto read<nlohmann::json> (const char* file) -> nlohmann::json {
//                  lock_guard<mutex> lock (mtx);
//            ifstream i (file);
//            nlohmann::json j1;
//            i >> j1;
//            return j1;
//      }
      
      template <>
      auto write (const char* file, const nlohmann::json& from) -> void {
                  lock_guard<mutex> lock (mtx);
            ph::file::write(file, from.dump());
      }
}


