#include "SoundManager.h"

SoundManager::SoundManager()
{

}

void SoundManager::Start()
{
    std::string soundName[] = {
        "Sounds/itemSound.wav",
        "Sounds/hitObjects.wav",
        "Sounds/hitPlayer.wav",
        "Sounds/scoreSound.wav",
        "Sounds/gameOverSound.wav"
        };

    musicName[0] = "Musics/menuMusic.wav";
    musicName[1] = "Musics/gameMusic.wav";

    std::cout<<"Loading Sounds..."<<std::endl;
    for(int i =0; i< numberOfSounds; i++){
        if (!buffer[i].loadFromFile(soundName[i]))
            std::cout<<"Failed to load \""<< soundName[i] <<"\" sound. Check if the file exists"<< std::endl;
        else
            std::cout<<"Sound \""<< soundName[i] <<"\" finished OK!"<< std::endl;
    }
}

void SoundManager::menuMusic(){
    if (!music[0].openFromFile(musicName[0]))
        std::cout<<"Failed to load \""<< musicName[0] <<"\" music. Check if the file exists"<< std::endl;
    music[1].stop();
    music[0].setLoop(true);
    music[0].play();
    music[0].setVolume(20);
}

void SoundManager::gameMusic(){
    if (!music[1].openFromFile(musicName[1]))
        std::cout<<"Failed to load \""<< musicName[1] <<"\" music. Check if the file exists"<< std::endl;
    music[0].stop();
    music[1].setLoop(true);
    music[1].play();
    music[1].setVolume(20);
}

void SoundManager::stopGameMusic(){
    music[1].stop();
}

void SoundManager::SoundTest()
{
    if(sound[0].getStatus() == 0){
        this->sound[0].setBuffer(this->buffer[0]);
        this->sound[0].play();
    }

    std::cout<<"Sound played?" <<this->sound[0].getStatus()<<std::endl;

}

void SoundManager::itemSelected(int item)
{
    if(item != lastItem && item != -1){
        this->sound[0].stop();
        this->sound[0].setBuffer(this->buffer[0]);
        this->sound[0].play();
    }
    lastItem = item;

}

void SoundManager::hitObjects()
{
    this->sound[1].setBuffer(this->buffer[1]);
    this->sound[1].play();

}

void SoundManager::hitPlayer()
{
    this->sound[2].setBuffer(this->buffer[2]);
    this->sound[2].play();

}

void SoundManager::scoreSound()
{
    this->sound[3].setBuffer(this->buffer[3]);
    this->sound[3].play();

}

void SoundManager::gameOverSound()
{
    this->stopGameMusic();
    this->sound[4].setBuffer(this->buffer[4]);
    this->sound[4].play();

}

int SoundManager::GetSoundStatus(){
    return sound[0].getStatus();
}

SoundManager::~SoundManager()
{
    //dtor
}
