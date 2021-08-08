std::pair<int, int> inCoordinates() override {
        std::string input;
        std::cin >> input;
        char first = std::toupper(input[0]);
        int iFirst;
        switch(first) {
            case 'A' :
                iFirst = 0;
                break;
            case 'B' :
                iFirst = 1;
                break;
            case 'C' :
                iFirst = 2;
                break;
            case 'D' :
                iFirst = 3;
                break;
            case 'E' :
                iFirst = 4;
                break;
            case 'F' :
                iFirst = 5;
                break;
            case 'G' :
                iFirst = 6;
                break;
            case 'H' :
                iFirst = 7;
                break;
            case 'I' :
                iFirst = 8;
                break;
            case 'J' :
                iFirst = 9;
                break;
            default :
                std::cout << "zle koordynaty idioto!\n";
                break;
        }
        char second = input[1];
        int iSecond = (int)second - 48;

        return std::make_pair(iFirst, iSecond);
    }