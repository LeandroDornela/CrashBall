#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <SFML/Audio.hpp>
#include <iostream>

class SoundManager
{
    public:
        SoundManager();
        virtual ~SoundManager();

        void SoundTest();
        void Start();
        void itemSelected(int item);
        void hitObjects();
        void hitPlayer();
        void scoreSound();
        void gameOverSound();

        void menuMusic();
        void gameMusic();
        void stopGameMusic();
        int GetSoundStatus();

    protected:

    private:
        int lastItem = -2;
        int numberOfSounds = 5;
        sf::SoundBuffer buffer[5];
        sf::Sound sound[5];
        sf::Music music[2];
        std::string musicName[2];
};

#endif // SOUNDMANAGER_H
