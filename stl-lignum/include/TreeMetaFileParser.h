#ifndef TREE_METAFILE_PARSER_H
#define TREE_METAFILE_PARSER_H
#include <stdlib.h>
#include <Table.h>
#include <Lex.h>


using namespace cxxadt;

class TreeMetaFileParser{
public:
  TreeMetaFileParser(const std::string& meta_file);
  TreeMetaFileParser& parse();
  std::string getParameterFile(const std::string& type);
  std::string getFunctionFile(const std::string& type);
  std::string getTreeInitializationFile(const std::string& type);
protected:
  TreeMetaFileParser& parseMetaFile();     //top level method to parse meta file
  TreeMetaFileParser& parseFiles();        //this method does the parsing by
  TreeMetaFileParser& parseFile();         //parsing one file at a time
private:
  enum FILE_MODE {PARAMETER,FUNCTION,INITIAL};
  FILE_MODE file_mode;
  Table<std::string,std::string> file_tables[3]; //tables for the parameter files and functions
  // and initialization files
  std::string meta_file;     //meta file (describes where the actual files exists)
  Lex lex;               //lexical analysator for tokenizing the input file
};


#endif //TREE_METAFILE_PARSER_H




