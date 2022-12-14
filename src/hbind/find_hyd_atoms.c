/*
 *
 *    find_hyd_atoms.c     Volker Schnecke     Fri Feb 13 14:42:40 EST 1998
 *
 *    functions:  check_hyd_atom()
 *                find_hyd_atoms()
 *
 *    checks all atoms in the structure to identify Hydrogen-bond
 *    donors and acceptors
 *    
 */

#include <stdio.h>
#include <types.h>
#include <defs.h>
#include <check_rule.h>

/*  This routine checks the atom with index 'index' in the molecule
 *  structure for donor or acceptor properties as described in 'rules'.
 *  The possible return values are DONOR, ACCEPTOR, or NOTHING 
 */
int check_hyd_atom(molecule_pt  molecule, hyd_defn_pt rules, int index )
{
  atom_pt  atoms;
  rule_pt  rule;
  int      result,
           temp_act;
  int      i, j;

  atoms = molecule->atoms; // person->gender
  temp_act = NOTHING;

  /* check acceptor rules first */
  for(i = 0; i < rules->number_of_acceptor_rules && temp_act == NOTHING; i++){
    rule = &rules->acceptor_rules[i]; // apples[5]

    /* atom matches current acceptor rule atom, so check required and
     * prohibited rules */
    if(check_atom(rule->type, rule->orbit, atoms[index].type, atoms[index].orbit)){
      result = SUCCESS; 
      for(j = 0; j < MAX_RULES_PER_BONDED_ATOM && result == SUCCESS; j++) 
        /* the third parameter is the index of a neighbored atom
         * that should not be included in the checks; this is only
         * relevant when checking flexible bond rules, so pass
         * index = -1 here */
        if(rule->prohibited[j] != NULL) 
          result = check_prohibited_rule(molecule, index, -1, rule->prohibited[j]);

      for(j = 0; j < MAX_RULES_PER_BONDED_ATOM && result == SUCCESS; j++) 
        if(rule->required[j] != NULL ) 
          result = check_required_rule(molecule, index, -1, rule->required[j]); 

      /* all rules fulfilled, i.e. this atom is an ACCEPTOR, but
       * don't return, check first, if this atom can donate, too */
      if(result == SUCCESS) temp_act = ACCEPTOR;
    }
  }

  /* if current atom is no acceptor, it might still be a donor... */
  for ( i = 0; i < rules->number_of_donor_rules; i++){ 
    rule = &rules->donor_rules[i]; 
    if(check_atom(rule->type, rule->orbit, atoms[index].type, 
                  atoms[index].orbit)){ 
      result = SUCCESS; 
      for(j = 0; j < MAX_RULES_PER_BONDED_ATOM && result == SUCCESS; j++) 
        if(rule->prohibited[j] != NULL) 
          result = check_prohibited_rule(molecule, index, -1, 
                                         rule->prohibited[j]); 
      for ( j = 0; j < MAX_RULES_PER_BONDED_ATOM && result == SUCCESS; j++) 
        if(rule->required[j] != NULL ) 
          result = check_required_rule(molecule, index, -1, rule->required[j]); 

      /* hit, so this atom is a donor, but has it already been 
       * identified as an acceptor? */
      if(result == SUCCESS){ 
        if(temp_act == ACCEPTOR) return DONEPTOR;
        else return DONOR;
      }
    }
  }

  /* definitely no donor, in that case the routine would have been left
     before, so it might be nothing or a acceptor, temp_hyd has the answer */
  return temp_act; // NOTHING, ACCEPTOR, DONOR, DONEPTOR
}

int check_hyd_atom_for_c(molecule_pt  molecule, int index )
/* index is the # of the reading atom */
{
  // req1: neighbors of C must have N & H
  // req2: neighbors of N must have at a C meet req3
  // req3: neighbors of C must have a 0 meet req4
  // req4: neighbors of O must have no neighbors
    atom_pt  atoms;
    //atom_pt  neighbor_atom;
    int      *neighbors;
    int      number_of_neighbors;
    int      temp_act = NOTHING;
    int      i, j;

    atoms = molecule->atoms;
    neighbors = molecule->neighbors[index];
    number_of_neighbors = molecule->number_of_neighbors[index];

    /* check if C has N & H */
    for (i = 0; i < number_of_neighbors; i++ )
    {
        if ( molecule->atoms[neighbors[i]].type == H )
        {
            for (j = 0; j < number_of_neighbors; j++)
            {
                if (molecule->atoms[neighbors[j]].type == N)
                    temp_act = DONOR;
                /*neighbor_atom = &molecule->atoms[neighbors[j]];
                neighbors = molecule->neighbors[neighbor_atom]; //how to change neighbor
                number_of_neighbors = molecule->number_of_neighbors[j];
                for (k = 0, k < number_of_neighbors; k++)
                    if (molecule->atoms[neighbors[i]].type == H) */
            }
        }
    }
    return temp_act;
}

/*  This routine checks all atoms in 'molecule' and assigns the 'hyd'
 *  properties to them
 */
void find_hyd_atoms(molecule_pt molecule, hyd_defn_pt rules)
{
  int i;

  for ( i = 0; i < molecule->number_of_atoms; i++ )
    /* only have a closer look at Nitrogens and Oxygens */
    if(molecule->atoms[i].type == N || molecule->atoms[i].type == O || 
       molecule->atoms[i].type == F || molecule->atoms[i].type == CL){
      molecule->atoms[i].act = check_hyd_atom(molecule, rules, i);
      /* add C-H as donor */
    } else if (molecule->atoms[i].type == C) {
        molecule->atoms[i].act = check_hyd_atom_for_c(molecule, i);
    } else molecule->atoms[i].act = NOTHING;
}
