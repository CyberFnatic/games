/* init.h initializes the starting position of the game
 * - Players
 * - Chance cards (Sattuma)
 * - Community Chest cards (Yhteismaa)
 */

// DECLARATIONS
void initBoard(Board &board);
void initPlayers(std::vector<Player> &players);
void initChance(Card (&chanceCards)[16]);
void initCommunity(Card (&communityCards)[16]);

void newGame(Board &board, std::vector<Player> &players, Card (&chanceCards)[16], Card (&communityCards)[16]) {
  initBoard(board);
  initPlayers(players);
  initChance(chanceCards);
  initCommunity(communityCards);
}

void initBoard(Board &board) {
  // Array of positions (squares) on the board
  std::string positions[40] = {
    "Lähtö",
    "Korkeavuorenkatu",
    "Yhteismaa",
    "Kasarmikatu",
    "Maksa tulovero",
    "Pasilan asema",
    "Rantatie",
    "Sattuma",
    "Kauppatori",
    "Esplanadi",
    "Vankila",
    "Hämeentie",
    "Sähkölaitos",
    "Siltasaari",
    "Kaisaniemenkatu",
    "Sörnäisten asema",
    "Liisankatu",
    "Yhteismaa",
    "Snellmaninkatu",
    "Unioninkatu",
    "Vapaa pysäköinti",
    "Lönnrotinkatu",
    "Sattuma",
    "Annankatu",
    "Simonkatu",
    "Rautatieasema",
    "Mikonkatu",
    "Aleksanterinkatu",
    "Vesilaitos",
    "Keskuskatu",
    "Mene vankilaan",
    "Tehtaankatu",
    "Eira",
    "Yhteismaa",
    "Bulevardi",
    "Tavara-asema",
    "Sattuma",
    "Mannerheimintie",
    "Maksa lisävero",
    "Erottaja"
  };

  int payments[40] = {
    0, -60, 0, -60, -200, -200, -100, 0, -100, -120,
    0, -140, -150, -140, -160, -200, -180, 0, -180, -200,
    0, -220, 0, -220, -240, -200, -260, -260, -150, -280,
    0, -300, -300, 0, -320, -200, 0, -350, -100, -400
  };
  
  for (int i=0; i<40; i++) {
    board.SetPosition(i, positions[i]);
    board.SetPayment(i, payments[i]);
  }
}

// TODO
void initPlayers(std::vector<Player> &players) {
  for (int i=0; i<PLAYER_AMOUNT; i++) {
    Player player;
    player.SetPlayerID(i);
    players.emplace_back(player);
  }
}

void initChance(Card (&chanceCards)[16]) {
  std::string cardTexts[16] = {
    // Property payments
    "Kaikkia kiinteistöjäsi on korjattava. Maksu kustakin talosta 25€, kustakin hotellista 100€.",
    "Maksa korvausta katujen kunnossapidosta 40€ talosta ja 115€ hotellista.",
    
    // Collect money + perks
    "Maksu rakennuslainastasi, peri 150€.",
    "Olet voittanut ristisanakilpailun, peri 100€.",
    "Saat nostaa pankista säästötilikorkoa 50€.",
    "Vapaudut vankilasta.",

    // Move to a location
    "Jatka matkaasi \"Lähtö\"-ruutuun.",
    "Jatka matkaasi Erottajalle.",
    "Jatka matkaasi Hämeentielle. Jos kuljet \"Lähtö\"-ruudun kautta, saat periä 200€.",
    "Jatka matkaasi Simonkadulle. Jos kuljet \"Lähtö\"-ruudun kautta saat periä 200€.",
    "Käväise Sörnäisten-asemalla. Jos kuljet \"Lähtö\"-ruudun kautta, saat periä 200€.",
    "Käväise Tavara-asemalla. Jos kuljet \"Lähtö\"-ruudun kautta, saat periä 200€.",
    "Mene kolme askelta taaksepäin.",
    "Mene vankilaan! Mene suoraan vankilaan kulkematta \"Lähtö\"-ruudun kautta.",

    // Payments
    "Maksa sakkoa ylinopeudesta 15€.",
    "Maksa koulumaksuja 150€."
  };

  int cardPayments[16] = { 0, 0, 150, 100, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, -15, -150 };

  for (int i=0; i<16; i++) {
    chanceCards[i].SetText(cardTexts[i]);
    chanceCards[i].SetType("Sattuma");
    chanceCards[i].SetPayment(cardPayments[i]);

    // Movement cards are indexes 6-13
    if (i >= 6 && i <= 13) {
      chanceCards[i].SetMustMove();

      switch (i) {
        case 6:
          chanceCards[i].SetMovePosition(0);  // Lähtö
          break;
        case 7:
          chanceCards[i].SetMovePosition(39); // Erottaja
          break;
        case 8:
          chanceCards[i].SetMovePosition(11); // Hämeentie
          break;
        case 9:
          chanceCards[i].SetMovePosition(24); // Simonkatu
          break;
        case 10:
          chanceCards[i].SetMovePosition(15); // Sörnäisten-asema
          break;
        case 11:
          chanceCards[i].SetMovePosition(35); // Tavara-asema
          break;
        case 12:
          chanceCards[i].SetMovePosition(-3); // 3 steps backwards
          chanceCards[i].SetMoveBackwards();
          break;
        case 13:
          chanceCards[i].SetMovePosition(20); // Vankila
          break;
        default:
          std::cout << "Sattumakortin '" << chanceCards[i].GetText() << "' alustaminen ei onnistunut!" << std::endl;
      } // End of switch-loop
    } // End of if-statement (movement cards)
  } // End of for-loop
} // End of initChance()

void initCommunity(Card (&communityCards)[16]) {
  std::string cardTexts[16] = {
    // Collect money + perks
    "Elinkorko erääntyy maksettavaksi. Peri 100€.",
    "Laskuvirhe pankissa sinun eduksesi. Peri 200€.",
    "Olet myynyt varastosta tavaraa. Peri 50€.",
    "Olet saanut toisen palkinnon kauneuskilpailussa. Peri 10€.",
    "On syntymäpäiväsi. Peri 10€ jokaiselta osanottajalta.",
    "Osinko 7\% etuoikeutetuista osakkeista. Peri 25€.",
    "Saat perintöä 100€.",
    "Veronpalautus peri 20€.",
    "Vapaudut vankilasta.",
    
    // Move to a location
    "Jatka matkaasi \"Lähtö\"-ruutuun.",
    "Mene vankilaan! Mene suoraan vankilaan kulkematta \"Lähtö\"-ruudun kautta.",
    "Palaa Korkeavuorenkadulle.",

    // Payments
    "Lääkärinpalkkio. Maksa 50€.",
    "Maksa sairaalamaksu 100€.",
    "Maksa sakkoa 10€ tai ota \"Sattuma\"-kortti.",
    "Maksa vakuutusmaksuja 50€."
  };

  int cardPayments[16] = { 100, 200, 50, 10, 0, 25, 100, 20, 0, 0, 0, 0, -50, -100, -10, -50 };

  for (int i=0; i<16; i++) {
    communityCards[i].SetText(cardTexts[i]);
    communityCards[i].SetType("Yhteismaa");
    communityCards[i].SetPayment(cardPayments[i]);

    // Movement cards are indexes 9-11
    if (i >= 9 && i <= 11) {
      communityCards[i].SetMustMove();

      switch (i) {
        case 9:
          communityCards[i].SetMovePosition(0); // Lähtö
          break;
        case 10:
          communityCards[i].SetMovePosition (10); // Vankila
          communityCards[i].SetMoveBackwards(); // Player cannot bypass "Lähtö" square
          break;
        case 11:
          communityCards[i].SetMovePosition (1); // Korkeavuorenkatu
          communityCards[i].SetMoveBackwards(); // Card requires to move backwards
          break;
        default:
          std::cout << "Yhteismaakortin '" << communityCards[i].GetText() << "' alustaminen ei onnistunut!" << std::endl;
      } // End of switch-loop
    } // End of if-statement (movement cards)
  } // End of for-loop
} // End of initCommunity()
