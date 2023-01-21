void update_STATO(){
  String str;
  set_led(STATO);
  switch (STATO) {
    case 0:
      str = "OZIOSO";
      break;
    case 1:
      str = "TESTING";
      break;
    case 2:
      str = "FINITO: Mail->";
      break;
    case 3:
      str = "AGGWIFI";
      break;
  }
  printSCR_yesnet();
  printSCR_STATO(str);
};
