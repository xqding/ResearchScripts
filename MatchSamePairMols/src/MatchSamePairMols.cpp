#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <openbabel/mol.h>
#include <openbabel/obconversion.h>

int main(int argc, char** argv)
{
  // read reference and query molecules
  std::string referenceMolFileName(argv[1]);
  std::string queryMolFileName(argv[2]);  
  OpenBabel::OBMol referenceMol; // reference molecule
  OpenBabel::OBMol queryMol; // query molecule
  OpenBabel::OBConversion conv(&std::cin, &std::cout);  
  conv.SetInFormat("pdb");
  conv.SetOutFormat("smi");  
  conv.ReadFile(&referenceMol, referenceMolFileName);
  conv.ReadFile(&queryMol, queryMolFileName);
  
  // get the SMILES string (can be used as SMARTS pattern)
  // using the reference molecule
  std::stringstream referenceMolSMILESStream;
  conv.Write(&referenceMol, &referenceMolSMILESStream);
  std::string referenceMolSMILESString;
  referenceMolSMILESStream >> referenceMolSMILESString;
  OpenBabel::OBSmartsPattern smartsPattern;
  smartsPattern.Init(referenceMolSMILESString);
  std::clog << "SMILES:" << referenceMolSMILESString << std::endl;
    
  // match the SMARTS pattern to the reference molecule and the query molecule
  // match reference molecule
  smartsPattern.Match(referenceMol);  
  std::vector< std::vector<int> > referenceMapList;
  referenceMapList = smartsPattern.GetUMapList();
  
  // match query molecule
  // and check that the query molecule is the same as the reference molecule
  std::vector< std::vector<int> > queryMapList;
  bool match_flag;
  match_flag = smartsPattern.Match(queryMol);
  if (!match_flag)
  {
    throw std::runtime_error("The query molecule is different from the reference molecule");
  }
  queryMapList = smartsPattern.GetUMapList();
  if (queryMapList[0].size() != queryMol.NumAtoms())
  {
    throw std::runtime_error("The query molecule is different from the reference molecule");
  }

  // change the coordinates of the query molecule
  for(int i = 0; i < queryMapList[0].size(); i++)
  {
    queryMol.GetAtom(queryMapList[0][i])->SetVector( referenceMol.GetAtom(referenceMapList[0][i])->GetVector() );
  }

  // output the modified query molecule to std::cout
  conv.SetOutFormat("pdb");
  conv.Write(&queryMol, &std::cout);  
  return 0;
}
