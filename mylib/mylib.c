void calcnextstate(int current1, int current2, int choice1, int choice2, int nextstate[2]){
  nextstate[0] = (choice1 & choice2) | ((!current1) & choice1);
  nextstate[1] = (choice1 & choice2) | ((!current2) & choice2);
}