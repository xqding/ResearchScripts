# MatchSamePairMols
Usage:
	./MatchSamePairMols reference_ligand.pdb query_ligand.pdb > query_ligand_match.pdb
	
Description:
	Given the pdb files of two same ligands: a reference ligand and a query ligand, MatchSamePairMols will modify the coordinate of the query ligand to be the same as the reference ligand. It is used when the two pdb files have differenct atom names or have different orders of atoms. It outputs the modified query ligand pdb file to standard output.
	
Example:
	./build/MatchSamePairMols ./test/reference_ligand.pdb ./test/query_ligand.pdb
