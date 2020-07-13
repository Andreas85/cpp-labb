#include <iostream>
#include <chrono>
#include <thread>
using namespace std;


class Object {
    public:
        int xPos;
        int yPos;
        Object (int, int);
        int get_x_pos() { return xPos; };
        int get_y_pos() { return yPos; };
        void move_down() { yPos++; };
};

Object::Object (int x, int y) {
    //cout << "Object construct" << endl;
    xPos = x;
    yPos = y;
}


class Predator : public Object {
    public:
        Predator (int x, int y) : Object (x, y) {
            //cout << "Predator construct" << endl;
            xPos = x;
            yPos = y;
        }

};

class Creature : public Object {
    public:
        Creature (int x, int y) : Object (x, y) {
            //cout << "Creature construct" << endl;
            xPos = x;
            yPos = y;
        }
        void move(int predator_x, int predator_y, int food_x, int food_y) {

            if (predator_y <= food_y) {
                if (predator_x >= 10 && xPos > 0) {
                    xPos--;
                } else if (predator_x < 10 && xPos < 18) {
                    xPos++;
                }
            } else {

                cout << "1§2321JOIJOI";
            }
        /*
            if (closest object enemy) {
                // Move away from
            } else if (closest object food) {
                // Move towards
            }
        */
        }
};

class Food : public Object {
    public:
        Food (int x, int y) : Object (x, y) {
            //cout << "Food construct" << endl;
            xPos = x;
            yPos = y;
        }
};

int main() {
    std::system("clear");

    Creature creature (5, 19);
    Predator predator (5, 2);
    Food food(8, 21);

    for (int y = 0; y < 22; y++) {
        cout << "_";
    }
    cout << endl;

    for (int r = 0; r < 100; r++) {
        std::system("clear");
        for (int y = 0; y < 20; y++) {
            cout << "|";
            for (int x = 0; x < 10; x++) {
                if (x == creature.get_x_pos() && y == creature.get_y_pos()) {
                    cout << "C ";
                } else if (x == predator.get_x_pos() && y == predator.get_y_pos()) {
                    cout << "P ";
                } else if (x == food.get_x_pos() && y == food.get_y_pos()) {
                    cout << "F ";
                } else {
                    cout << "  ";
                }
            }
            cout << "|" << endl; 
        }
        food.move_down();
        predator.move_down();
        creature.move(predator.get_x_pos(), predator.get_y_pos(), food.get_x_pos(), food.get_y_pos());
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
