#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<list>
#include<rapidxml.hpp>
#include<rapidxml_print.hpp>

bool openXML(std::string path, rapidxml::xml_document<> &xml);
std::string openHTML(std::string path);
std::string get_resources(rapidxml::xml_document<> &xml);
std::string get_text(rapidxml::xml_document<> &xml);
int main() {

        rapidxml::xml_document<> xml;
        rapidxml::xml_document<> resource_file;
        rapidxml::xml_document<>contain_file;
        openXML("./container.xml", xml);
       std::string resource_file_name = get_resources(xml);

        if(resource_file_name.compare("") == 0) {
      //      return -1;
        }
        else{

            openXML(resource_file_name, resource_file);
            print(std::cout, resource_file, 0);
        }
std::cout<<"-------------------------------------------------------------------"<<std::endl;
std::cout<<"-------------------------------------------------------------------"<<std::endl;
std::cout<<"-------------------------------------------------------------------"<<std::endl;

            std::string contain_file_name = get_text(resource_file);
            //openXML(contain_file_name,contain_file);
            //print(std::cout,contain_file,0);


return 0;
}


bool openXML(std::string path, rapidxml::xml_document<> &xml) {
     std::ifstream file(path);
    std::stringstream buffer;
    if(file){
        buffer << file.rdbuf();
        file.close();
        std::string content = buffer.str();
        xml.parse<0>((char*)&content[0]);
        return true;
    }
    return false;
}

std::string get_resources(rapidxml::xml_document<> &xml)
{
    rapidxml::xml_node<> * root_node = xml.first_node("container");
        if(root_node == 0) return "";
        rapidxml::xml_node<> * rootfiles_node = root_node->first_node("rootfiles");
        rapidxml::xml_node<> * rootfile_node = rootfiles_node->first_node("rootfile");

      rapidxml::xml_attribute<> * path_attribute = rootfile_node->first_attribute("full-path");

            if(path_attribute != 0)
                return path_attribute->value();
                else return "";
}

std::string get_text(rapidxml::xml_document<> &xml)
{
    rapidxml::xml_node<> * package_node = xml.first_node("package");
    rapidxml::xml_node<> * manifest_node =package_node->first_node("manifest");
    for(rapidxml::xml_node<> * items_node = manifest_node->first_node("item"); items_node; items_node = items_node->next_sibling()) {
   //
   if (items_node != 0) {
      rapidxml::xml_attribute<> * path_attribute = items_node->first_attribute("href");
            rapidxml::xml_document<>contain_file;
            std::string name;
            name = path_attribute->value();
           if((path_attribute != 0) && !(name.empty()))
            {
                std::cout<<name <<std::endl;
                std::cout<<openHTML(name);
          //
         }
              //if(path_attribute != 0)
           //     return path_attribute->value();
           //     else return "";
        }
    }
    return "";
}

std::string openHTML(std::string path) {
     std::ifstream file(path);
    std::stringstream buffer;
    if(file){
        buffer << file.rdbuf();
        file.close();
        std::string content = buffer.str();
        return content;
    }
    return "";
}

