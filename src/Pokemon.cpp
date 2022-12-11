#include <iostream>
#include <glm/glm.hpp>
using namespace std;

// give it a random destination and let it walk there
// if reach destination, give it a new destination
class Pokemon
{
private:
    float x;
    float y;
    float z;
    float destinationX;
    float destinationY;
    float destinationZ;
    float speed;
    float direction;
    int beenCaught;
    int flyPokemon;
    int pokemonID;

public:
    static float random(float min, float max)
    {
        return ((float)rand() / RAND_MAX) * (max - min) + min;
    }

    Pokemon()
    {
        x = random(-100, 100);
        y = random(20, 50);
        z = random(-100, 100);
        speed = 0.01;
        beenCaught = 0;
    }

    ~Pokemon() {}

    Pokemon(int flyPokemon, int pokemonID)
    {
        this->pokemonID = pokemonID;
        this->flyPokemon = flyPokemon;
        x = random(-100, 100);
        z = random(-100, 100);

        beenCaught = 0;

        if (flyPokemon)
        {
            y = random(15, 35);
            float newY = random(-10, 10);
            speed = 0.05;
            setDestination(x + random(-20, 20),
                           y + newY,
                           z + random(-20, 20));
        }
        else
        {
            y = 0;
            speed = 0.01;
            setDestination(x + random(-5, 5),
                           y + 0,
                           z + random(-5, 5));
        }

        cout << "Pokemon " << pokemonID << " created at " << x << " " << y << " " << z << endl;
        cout << "Destination is " << destinationX << " " << destinationY << " " << destinationZ << endl;
    }

    void update(int pokemonID)
    {
        if (isAtDestination())
        {
            if (flyPokemon)
            {
                float newY = random(-10, 10);

                setDestination(x + random(-20, 20),
                               y + newY,
                               z + random(-20, 20));
            }
            else
            {
                setDestination(x + random(-5, 5),
                               y + 0,
                               z + random(-5, 5));
            }
        }
        // just address a bug, solve it later
        if (flyPokemon && y < 10)
        {
            y = 20;
            setDestination(x, y, z);
        }
        walkToDestination(pokemonID);
    }

    void setCaught(int flag) { beenCaught = flag; }

    int getCaught() { return beenCaught; }

    void setDestination(float x, float y, float z)
    {
        destinationX = x;
        destinationY = y;
        destinationZ = z;
    }

    glm::vec3 getPos() { return glm::vec3(x, y, z); }

    void walkToDestination(int pokemonID)
    {
        // walk to destination from a point walk to another point

        // get the direction
        glm::vec3 direction = glm::vec3(destinationX - x, destinationY - y, destinationZ - z);
        // normalize the direction
        direction = normalize(direction);
        // // move the pokemon
        x += direction.x * speed;
        y += direction.y * speed;
        z += direction.z * speed;
    }

    int isAtDestination()
    {
        // check if reach destination
        if ((abs(x - destinationX) < 0.5) && (abs(y - destinationY) < 0.5) &&
            (abs(z - destinationZ) < 0.5))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    int getID() { return pokemonID; }
};