## User Guide

To execute Hbind, please navigate to its main directory from where you installed it and run the following command to identify the hydrogen bonds in a protein ligand interface:

    ./bin/hbind -p ./example_files/1KPF.pdb \
    -l ./example_files/1KPF_AMP.mol2 

Here, 1KPF.pdb is an excerpt from the PDB structure [1KPF](https://www.rcsb.org/pdb/explore.do?structureId=1kpf) (PKCI-substrate analog) with its ligand `1KPF_AMP.mol2` (adenosine monophsophate). The structures are provided in Hbind's subdirectory "[example_files/](https://github.com/rasbt/Hbind/tree/master/example_files)".

***Before you run Hbind, please make sure that you provide the protein structure in PDB format and the ligand structure in MOL2 format, and please ensure that the ligand's protonation state (hydrogen assignment) is correct.***

To protonate a ligand, tools such as [OpenEye MolCharge](https://docs.eyesopen.com/quacpac/molchargeusage.html) can be used. However, it is recommended to protonate a ligand in presence of its protein environment, for example, by using tools such as [What If](http://swift.cmbi.ru.nl/whatif/) or [Yasara OptHyd](http://www.yasara.org/features.htm).

After running the command from the beginning of this section, the following output should be displayed:

```
HBIND Version: 1.0.0

Documentation: http://psa-lab.github.io/Hbind
Raschka, Wolf, Bemister-Buffington, Kuhn (2018)
Protein Structure and Analysis Lab, MSU (http://kuhnlab.bmb.msu.edu)

Ligand file: /Users/sebastian/code/hbind/example_files/1KPF_AMP.mol2
Protein file: /Users/sebastian/code/hbind/example_files/1KPF.pdb

++++++++++++++++++++++++++++++++ HBind Interaction Table ++++++++++++++++++++++++++++++++
#            | Ligand Atom -- Protein  Atom | Bond                D-H-A  Lig.-Prot.
#            |  #  TYPE    -- RES  CH_ID  RES_NO  A_TYPE | DIST.  ANGLE  INTERACTION
| hbond     1   2  O.2     -- ASN  A       99     ND2      2.911  174.0  Acceptor - Donor
| hbond     2   3  O.3     -- SER  A      107     N        2.802  166.8  Acceptor - Donor
| hbond     3   3  O.3     -- VAL  A      108     N        3.031  178.8  Acceptor - Donor
| hbond     4   4  O.3     -- HIS  A      112     NE2      2.593  163.1  Acceptor - Donor
| hbond     5   4  O.3     -- HIS  A      114     NE2      2.581  140.4  Acceptor - Donor
| hbond     6  10  O.3     -- ASP  A       43     OD2      2.714  167.1  Donor - Acceptor
| hbond     7  12  O.3     -- ASP  A       43     OD1      2.607  154.1  Donor - Acceptor
| hbond     8  22  N.ar    -- ILE  A       44     N        3.156  154.9  Acceptor - Donor
```

To include salt bridges in the listing, you can use the `-s` option as shown below:

    ./bin/hbind -p ./example_files/1KPF.pdb \
    -l ./example_files/1KPF_AMP.mol2 -s

```
HBIND Version: 1.0.0

Documentation: http://psa-lab.github.io/Hbind
Raschka, Wolf, Bemister-Buffington, Kuhn (2018)
Protein Structure and Analysis Lab, MSU (http://kuhnlab.bmb.msu.edu)

Ligand file: /Users/sebastian/code/hbind/example_files/1KPF_AMP.mol2
Protein file: /Users/sebastian/code/hbind/example_files/1KPF.pdb

++++++++++++++++++++++++++++++++ HBind Interaction Table ++++++++++++++++++++++++++++++++
#            | Ligand Atom -- Protein  Atom | Bond                D-H-A  Lig.-Prot.
#            |  #  TYPE    -- RES  CH_ID  RES_NO  A_TYPE | DIST.  ANGLE  INTERACTION
| hbond     1   2  O.2     -- ASN  A       99     ND2      2.911  174.0  Acceptor - Donor
| hbond     2   3  O.3     -- SER  A      107     N        2.802  166.8  Acceptor - Donor
| hbond     3   3  O.3     -- VAL  A      108     N        3.031  178.8  Acceptor - Donor
| hbond     4   4  O.3     -- HIS  A      112     NE2      2.593  163.1  Acceptor - Donor
| hbond     5   4  O.3     -- HIS  A      114     NE2      2.581  140.4  Acceptor - Donor
| hbond     6  10  O.3     -- ASP  A       43     OD2      2.714  167.1  Donor - Acceptor
| hbond     7  12  O.3     -- ASP  A       43     OD1      2.607  154.1  Donor - Acceptor
| hbond     8  22  N.ar    -- ILE  A       44     N        3.156  154.9  Acceptor - Donor
| saltb     1   2  O.2     -- HIS  A      114     NE2      4.245  N/A    Acceptor - Donor
| saltb     2   3  O.3     -- HIS  A      112     NE2      3.382  N/A    Acceptor - Donor
| saltb     3   4  O.3     -- HIS  A      114     ND1      4.462  N/A    Acceptor - Donor
| saltb     4  10  O.3     -- ASP  A       43     OD1      3.395  N/A    Donor - Acceptor
| saltb     5  12  O.3     -- ASP  A       43     OD2      3.607  N/A    Donor - Acceptor
```

For additional information, i.e. a summary talbe that includes the number of hydrophobic contacts or [SLIDE](http://www.kuhnlab.bmb.msu.edu/software/slide/) docking scores, provide the `-t` flag:

    ./bin/hbind -p ./example_files/1KPF.pdb \
    -l ./example_files/1KPF_AMP.mol2 -s -t

```
HBIND Version: 1.0.0

Documentation: http://psa-lab.github.io/Hbind
Raschka, Wolf, Bemister-Buffington, Kuhn (2018)
Protein Structure and Analysis Lab, MSU (http://kuhnlab.bmb.msu.edu)

Ligand file: /Users/sebastian/code/hbind/example_files/1KPF_AMP.mol2
Protein file: /Users/sebastian/code/hbind/example_files/1KPF.pdb

+++++++++++++++++ Summary +++++++++++++++++++
| Protein-Ligand Hydrophobic Contacts :    39
| Protein-Ligand H-bonds              :     8
| Protein-Ligand Salt-bridges         :     5
| Metal-Ligand Bonds                  :     0
| SLIDE OrientScore                   : -8.787
| SLIDE AffiScore (heavy atoms)       : -0.102
| SLIDE AffiScore                     : -7.557

++++++++++++++++++++++++++++++++ HBind Interaction Table ++++++++++++++++++++++++++++++++
#            | Ligand Atom -- Protein  Atom | Bond                D-H-A  Lig.-Prot.
#            |  #  TYPE    -- RES  CH_ID  RES_NO  A_TYPE | DIST.  ANGLE  INTERACTION
| hbond     1   2  O.2     -- ASN  A       99     ND2      2.911  174.0  Acceptor - Donor
| hbond     2   3  O.3     -- SER  A      107     N        2.802  166.8  Acceptor - Donor
| hbond     3   3  O.3     -- VAL  A      108     N        3.031  178.8  Acceptor - Donor
| hbond     4   4  O.3     -- HIS  A      112     NE2      2.593  163.1  Acceptor - Donor
| hbond     5   4  O.3     -- HIS  A      114     NE2      2.581  140.4  Acceptor - Donor
| hbond     6  10  O.3     -- ASP  A       43     OD2      2.714  167.1  Donor - Acceptor
| hbond     7  12  O.3     -- ASP  A       43     OD1      2.607  154.1  Donor - Acceptor
| hbond     8  22  N.ar    -- ILE  A       44     N        3.156  154.9  Acceptor - Donor
| saltb     1   2  O.2     -- HIS  A      114     NE2      4.245  N/A    Acceptor - Donor
| saltb     2   3  O.3     -- HIS  A      112     NE2      3.382  N/A    Acceptor - Donor
| saltb     3   4  O.3     -- HIS  A      114     ND1      4.462  N/A    Acceptor - Donor
| saltb     4  10  O.3     -- ASP  A       43     OD1      3.395  N/A    Donor - Acceptor
| saltb     5  12  O.3     -- ASP  A       43     OD2      3.607  N/A    Donor - Acceptor
```

<br>
<br>




## Hydrogen bond rules

Hbind's rules for identifying hydrogen bonds protein-ligand interfaces are based on the criteria by Ippolito et al. [1] and McDonald and Thornton [2].

#### Hydrogen bond criteria:

- Hydrogen to acceptor distance: 1.5-2.5 A??
- Donor to acceptor distance: 2.4-3.5 A??
- Donor-H-acceptor angle (??): 120-180??
- Pre-acceptor???acceptor???H angle (??): 90-180??

(Hydrogen bonds must meet all of these criteria.)

#### Criteria for metal interactions:

- Lone pair atom distance to K or Na: 2.0-2.9 A??
- Lone pair atom distance to Ca, Co, Cu, Fe, Mg, Mn, Ni, or Zn: 1.7-2.6 A??

Additional command line options are available to list longer-range salt bridge interactions (up to 4.5 A??) and the number of hydrophobic contancts between protein and ligand atoms.


[1] Ippolito, Joseph A, Richard S Alexander & David W Christianson. 1990. Hydrogen bond stereo-chemistry in protein structure and function. *Journal of Molecular Biology* 215(3). 457???471.   
[2] McDonald, Ian & Janet M Thornton. 1994. Atlas of side-chain and main-chain hydrogen bonding. http://www.biochem.ucl.ac.uk/bsm/atlas: Biochemistry and Molecular Biology Department, University College London.

<br>
<br>
