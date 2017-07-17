#include "Interface.h"
#include "GL/glut.h"
#include <iostream>
#include <fstream>
#include <cstring>

Interface::Interface(bool fullscreen)
{
    this->score = new glcText();
    this->score->setType(5);
    this->score->setPos(glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH)/2 - 20, glutGet((fullscreen) ? GLUT_SCREEN_HEIGHT : GLUT_WINDOW_HEIGHT) - 15);
    this->score->setString("Score");
    this->timeElapsed = new glcText();
    this->timeElapsed->setType(5);
    this->timeElapsed->setPos(glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH)/2 - 20, glutGet((fullscreen) ? GLUT_SCREEN_HEIGHT : GLUT_WINDOW_HEIGHT) - 30);
    this->timeElapsed->setString("0:00");

    char* menuItems[] = {"singlePlayer", "multiplayer", "difficulty", "ranking", "quit"};
    this->mainMenu = new Menu(1.0, 1.0, 1.0, sizeof(menuItems)/sizeof(*menuItems), 512, 64, menuItems, fullscreen);

    char* gameLevels[] = {"easy", "medium", "hard", "back"};
    this->levelMenu = new Menu(1.0, 1.0, 1.0, sizeof(gameLevels)/sizeof(*gameLevels), 512, 64, gameLevels, fullscreen);

    char* pauseOptions[] = {"continue", "restartGame","inspectMode", "quitGame"};
    this->pauseMenu = new Menu(1.0, 1.0, 1.0, sizeof(pauseOptions)/sizeof(*pauseOptions), 512, 64, pauseOptions, fullscreen);

    this->SetnBestTimes(0);
    /*
    this->singlePlayer = new glcText();
    this->singlePlayer->setType(5);
    this->singlePlayer->setPos(480 - 50, 250);
    this->singlePlayer->setString("Single Player");
    this->multiPlayer = new glcText();
    this->multiPlayer->setType(5);
    this->multiPlayer->setPos(480 - 50, 270);
    this->multiPlayer->setString("Multiplayer");
    this->records = new glcText();
    this->records->setType(5);
    this->records->setPos(480 - 50, 290);
    this->records->setString("Ranking");
    this->SetstartTime(time(NULL));
    */

    bgTexture = new glcTexture();            // Criação do arquivo que irá gerenciar as texturas
    bgTexture->SetNumberOfTextures(100);       // Estabelece o número de texturas que será utilizado
    bgTexture->SetWrappingMode(GL_REPEAT);

    std::string imagePath = "../data/menu/background.png";
    bgTexture->CreateTexture(imagePath, 0);
}

void Interface::UpdateWindow(int w, int h){
    this->mainMenu->Setwidth(w);
    this->mainMenu->Setheight(h);
    this->levelMenu->Setwidth(w);
    this->levelMenu->Setheight(h);
    this->pauseMenu->Setwidth(w);
    this->pauseMenu->Setheight(h);
}

void Interface::bgMenu(float width, float length, float x, float y, float z, int nx, int ny, int nz, bool fullscreen)
{
        glDisable(GL_LIGHTING);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH), glutGet((fullscreen) ? GLUT_SCREEN_HEIGHT : GLUT_WINDOW_HEIGHT), 0.0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();


	    this->bgTexture->Bind(0);
	    glBegin(GL_QUADS);
            glNormal3f(nx, ny, nz);
            glTexCoord2f(0, 1);
            glVertex3f(-width/2 + x, -length/2 + y, z);
            glTexCoord2f(0, 0);
            glVertex3f(-width/2 + x, length/2 + y, z);
            glTexCoord2f(1, 0);
            glVertex3f(width/2 + x, length/2 + y, z);
            glTexCoord2f(1, 1);
            glVertex3f(width/2 + x, -length/2 + y, z);
        glEnd();

    glEnable(GL_LIGHTING);
    glutPostRedisplay();
}


Interface::~Interface()
{
    //dtor
}

int Interface::MousePassiveMovement(int x, int y, int gameStatus){

    switch(gameStatus)
    {
        //1-menu, 2-single player, 3-multi player 4-ranking 5-developer mode 6-level screen 7-pause screen
        case 1:
            return this->mainMenu->texturePassiveSelection(x, y);
        break;
        case 2:
        break;
        case 3:
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
            return this->levelMenu->texturePassiveSelection(x, y);
        break;
        case 7:
            return this->pauseMenu->texturePassiveSelection(x, y);
        break;
    }
    glutPostRedisplay();
}

int Interface::MainMenuUpdate(int x, int y, int level)
{
    switch(mainMenu->GetselectedItem()){
        case 0:  //Single Player
            this->SetstartTime(time(NULL));
            return 2;
        break;
        case 1: //Multiplayer
            this->SetstartTime(time(NULL));
            return 3;
        break;
        case 2: //Difficulty
            /**TODO: IMPLEMENTAR TELA DE SELEÇÃO DE DIFICULDADE
                SERÁ NECESSÁRIO CRIAR MAIS UM STATUS DE GAME PRA ESSA TELA E UM MENU COM AS DIFICULDADES
                RETORNAR ESSE STATUS DE GAME AQUI AO INVÉS DE RETORNAR 1 (QUE INDICA MENU PRINCIPAL)
                criado status 6 para tal tela
            */
            return 6;
        break;
        case 3: // Ranking
            this->SetstartTime(-1);
            this->Ranking(level);
            return 4;
        break;
        case 4: //Quit
            exit(0);
            break;
        default: //Continua no menu principal
            return 1;
        break;
    }
}

int Interface::LevelMenuUpdate(int x, int y)
{
    switch(levelMenu->GetselectedItem()){
        case 0:  //Easy
            /**TODO: ALTERAR A DIFICULDADE PRA EASY*/
            return 0;
        break;
        case 1: //MEDIUM
            /**TODO: ALTERAR A DIFICULDADE PRA MEDIUM*/
            return 1;
        break;
        case 2: //HARD
            /**TODO: ALTERAR A DIFICULDADE PRA HARD*/
            return 2;
        break;
        case 3: //BACK
            return 3;
        break;
        default: //Continua no menu de dificuldade
            return 6;
        break;
    }
}

int Interface::PauseMenuUpdate(int x, int y)
{
    //"Continue", "Restart Game","Inspect Mode", "Quit Game"};
    switch(pauseMenu->GetselectedItem()){
        case 0:  //CONTINUE
            this->SetstartTime(this->GetstartTime() + (time(NULL) - this->GetpauseTime()) );
            return 0;
        break;
        case 1: //RESTART GAME
            /**TODO: resetar jogo atual e começar novo jogo*/
            this->SetstartTime(time(NULL));
            return 1;
        break;
        case 2: //INSPECT MODE
            /**TODO: ALTERAR A PARA O INSPECT MODE, DECIDIR SE ELE SERÁ O MESMO QUE DEVELOPER MODE ATUAL*/
            return 2;
        break;
        case 3: //QUIT GAME
            return 3;
        break;
        default: //Continua no menu de pause
            return 7;
        break;
    }
}

int Interface::InGameUpdate(int scoreP1, int scoreP2)
{
    char temp[6];
    snprintf(temp, 6, "%i X %i", scoreP1, scoreP2);
    this->score->setString(temp);
    int sec = time(NULL) - this->GetstartTime();
    int minutes = sec /60;
    sec = sec % 60;
    temp[4] = 0; //Limpando o elemento que não será sobreposto
    snprintf(temp, 6, "%i:%i", minutes, sec);
    if(sec < 10){
        temp[3] = temp[2];
        temp[2] = '0';
    }
    this->timeElapsed->setString(temp);

    return sec;
}

void Interface::DrawMainMenu(bool fullscreen)
{
    this->bgMenu(glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH), glutGet((fullscreen) ? GLUT_SCREEN_HEIGHT : GLUT_WINDOW_HEIGHT), glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH)/2, glutGet((fullscreen) ? GLUT_SCREEN_HEIGHT : GLUT_WINDOW_HEIGHT)/2, -0.1, 0, 0, 1, fullscreen);
    this->mainMenu->textureDraw();
}

void Interface::DrawLevelMenu(bool fullscreen)
{
    this->bgMenu(glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH), glutGet((fullscreen) ? GLUT_SCREEN_HEIGHT : GLUT_WINDOW_HEIGHT), glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH)/2, glutGet((fullscreen) ? GLUT_SCREEN_HEIGHT : GLUT_WINDOW_HEIGHT)/2, -0.1, 0, 0, 1, fullscreen);
    this->levelMenu->textureDraw();
}

void Interface::DrawPauseMenu(bool fullscreen)
{
    this->bgMenu(glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH), glutGet((fullscreen) ? GLUT_SCREEN_HEIGHT : GLUT_WINDOW_HEIGHT), glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH)/2, glutGet((fullscreen) ? GLUT_SCREEN_HEIGHT : GLUT_WINDOW_HEIGHT)/2, -0.1, 0, 0, 1, fullscreen);
    this->pauseMenu->textureDraw();
}

void Interface::DrawInGame(bool fullscreen)
{
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0.0, glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH), 0.0, glutGet((fullscreen) ? GLUT_SCREEN_HEIGHT : GLUT_WINDOW_HEIGHT));
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();

            this->score->setColor(1.0, 1.0, 1.0);
            this->score->render();
            this->timeElapsed->setColor(1.0, 1.0, 1.0);
            this->timeElapsed->render();

            glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glutPostRedisplay();
}

int Interface::ConvertStringTimeToInt(std::string myTime){

    int sec_int = 0;

    for(int i = 0; i < myTime.length(); i++){
        sec_int *= 10;
        sec_int = sec_int + ((int)myTime[i] - (int)'0');
    }

    return sec_int;
}

std::string Interface::ConvertIntToStringTime(int myInt)
{
    std::string strTime;

    int index = 0, aux;
    if(myInt <=0 ){
        return "0";
    }
    while(myInt > 0){
        aux = myInt % 10;
        strTime.insert(0, (const char*)((int)('0') + aux));
        myInt /= 10;
    }

    return strTime;
}

void Interface::LoadRanking(int level)
{
    int counter = 0;
    std::string line;

    /** Abrindo o ranking.txt para leitura **/
    std::ifstream read_ranking;

    switch(level){
        case 0:
            read_ranking.open("ranking_easy.txt");
            break;
        case 1:
            read_ranking.open("ranking_medium.txt");
            break;
        case 2:
            read_ranking.open("ranking_hard.txt");
            break;
        default:
            read_ranking.open("ranking_medium.txt");
            break;
    }

    /** Faz leitura e armazenamento no vetor de records **/
    if(read_ranking.fail() == false){
        std::cout<<"opened file to read count:"<<counter<<std::endl;
        while( std::getline (read_ranking, bestNames[counter], ' ') && counter < 10 ){

            std::getline (read_ranking, line, '\n');
            std::cout<<"Load line "<<counter<<": "<<bestNames[counter]<<" "<<line<<std::endl;
            bestTimes[counter] = this->ConvertStringTimeToInt(line);
            counter++;
        }
        std::cout<<"end of for count:"<<counter<<std::endl;
        read_ranking.close();
        SetnBestTimes(counter);
    }
    else{
        std::cout <<"\n :::: Falha ao abrir ranking! :::: \n";
    }
}

void Interface::SaveRanking(int level)
{
    std::string line;

    /** Abrindo o ranking.txt para escrita **/
    std::ofstream write_ranking;
    switch(level){
        case 0:
            write_ranking.open("ranking_easy.txt", std::fstream::trunc);
            break;
        case 1:
            write_ranking.open("ranking_medium.txt", std::fstream::trunc);
            break;
        case 2:
            write_ranking.open("ranking_hard.txt", std::fstream::trunc);
            break;
        default:
            write_ranking.open("ranking_medium.txt", std::fstream::trunc);
            break;
    }

    if(write_ranking.is_open()){
        std::cout<<"opened file to write"<<GetnBestTimes()<<std::endl;
        for (int i = 0; i < this->GetnBestTimes(); i++){
            std::cout<<"Save record "<<i<<": "<<bestNames[i]<<" "<<bestTimes[i]<<std::endl;
            //line = this->ConvertIntToStringTime(bestTimes[i]);
            //std::cout<<"Save line "<<i<<": "<<line<<std::endl;
            write_ranking << bestNames[i] << ' ' << bestTimes[i] << '\n';

        }
        write_ranking.close();
    }
    else{
        std::cout <<"\n :::: Falha ao abrir ranking! :::: \n";
    }
}

bool Interface::Ranking(int level)
{
    this->LoadRanking(level);

    int gameTime, aux;
    std::string nameAux = playername;
    bool indexed = false;

    if(this->GetstartTime() > 0){
        gameTime = time(NULL) - this->GetstartTime();
        /** Verifica se o tempo de jogo foi menor que algum tempo do ranking **/
        for(int i = 0; i < this->GetnBestTimes(); i++){
            if(this->bestTimes[i] >= gameTime){
                aux = bestTimes[i];
                nameAux = bestNames[i];
                bestTimes[i] = gameTime;
                bestNames[i] = playername;
                /** Guarda a posição em que foi inserido para destacar depois **/
                if(!indexed){
                    this->Setindex(i);
                    indexed = true;
                }
                /** Usado para empurrar os demais tempos para trás **/
                gameTime = aux;
            }
        }
        if(this->GetnBestTimes() < 10){
            bestTimes[this->GetnBestTimes()] = gameTime;
            bestNames[this->GetnBestTimes()] = nameAux;
            if(!indexed){
                /** Caso o tempo do último jogo tenha sido inserido no último da lista**/
                this->Setindex(this->GetnBestTimes());
                indexed = true;
            }
            this->SetnBestTimes(this->GetnBestTimes() + 1);
        }
    }
    std::cout<<"Returning from ranking...indexed ="<<indexed<<std::endl;
    return indexed;
}

int Interface::dealWithKey(char key, int level)
{
    std::cout<<"Nome ate agr: "<<playername<<std::endl;
    std::cout<<"Dealing with key '"<<key<<"'"<<std::endl;
    if( ((int)key >= (int)('a') && (int)key <= (int)('z'))
      ||((int)key >= (int)('A') && (int)key <= (int)('Z'))
      ||((int)key >= (int)('0') && (int)key <= (int)('9')) ){
          if(playername.size() < 10){
            playername.push_back( key);
          }
    } else if( (int)key == 8){
        if(playername.size() > 0){
            playername.erase(playername.size()-1);
        }
    } else if( (int)key == 13){
        bestNames[this->Getindex()]= playername;
        playername.empty();
        this->SaveRanking(level);
        return 4;
    }

    return 8;
}

void Interface::DrawPlayerName(bool fullscreen)
{
    glcText *name = new glcText();


    this->bgMenu(glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH), glutGet((fullscreen) ? GLUT_SCREEN_HEIGHT : GLUT_WINDOW_HEIGHT), glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH)/2, glutGet((fullscreen) ? GLUT_SCREEN_HEIGHT : GLUT_WINDOW_HEIGHT)/2, -0.1, 0, 0, 1, fullscreen);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    name->setAll("Ah muleke!!Me fala um nome pra colocar no ranking(max. 10 chars):", 5, glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH)/2 - 260, 200, 0.9, 0.9, 0.9);
    name->setAll(stringToChar(playername), 5, glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH)/2 - 60, 400, 0.9, 0.9, 0.9);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glutPostRedisplay();
    //std::cout<<"apareceu?"<<std::endl;
}

char *Interface::stringToChar(std::string c)
{
    char *ch = new char[c.length()+1];
    memcpy(ch, c.c_str(), c.length() + 1);
    return ch;
}

void Interface::DrawRanking(int level, bool fullscreen){

    this->bgMenu(glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH), glutGet((fullscreen) ? GLUT_SCREEN_HEIGHT : GLUT_WINDOW_HEIGHT), glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH)/2, glutGet((fullscreen) ? GLUT_SCREEN_HEIGHT : GLUT_WINDOW_HEIGHT)/2, -0.1, 0, 0, 1, fullscreen);

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    int sec;
    int minutes;
    char label[22];
    char* rankingLevel;
    switch(level){
    case 0:
        rankingLevel = "Ranking - Easy";
        break;
    case 1:
        rankingLevel = "Ranking - Medium";
        break;
    case 2:
        rankingLevel = "Ranking - Hard";
        break;
    }

    glcText *temp = new glcText();
    temp->setAll(rankingLevel, 5, glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH)/2 - 60, 200, 1.0, 1.0, 1.0);

    for(int i = 0; i < this->GetnBestTimes(); i++){
        temp->setPos(glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH)/2 - 60, 250 + i*30);
        this->Getindex() == i ? temp->setColor(0.9, 0.9, 0.0) : temp->setColor(0.9, 0.9, 0.9);

        minutes = this->bestTimes[i] / 60;
        sec = this->bestTimes[i] % 60;

        snprintf(label, 22, "%i- %s %im%is", i+1, stringToChar(bestNames[i]), minutes, sec);

        temp->setString(label);
        temp->render();
    }

    temp->setAll("Click to go to main menu", 5, glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH)/2 - 100, 570, 1.0, 1.0, 1.0);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glutPostRedisplay();
}
