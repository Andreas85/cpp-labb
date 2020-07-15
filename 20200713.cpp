#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
using namespace std;

int field_width = 20;
int field_height = 30;

class Object {
    public:
        int xPos;
        int yPos;
        Object (int, int);
        int get_x_pos() { return xPos; };
        int get_y_pos() { return yPos; };
        bool move_down() {
            if (yPos == field_height) {
                return false;
            }
            yPos++;
            return true;
        };
};

Object::Object (int x, int y) {
    xPos = x;
    yPos = y;
}

class Predator : public Object {
    public:
        Predator (int x, int y) : Object (x, y) {
            xPos = x;
            yPos = y;
        }

};

class Food : public Object {
    public:
        Food (int x, int y) : Object (x, y) {
            xPos = x;
            yPos = y;
        }
};

class Creature : public Object {
    public:
        Creature (int x, int y) : Object (x, y) {
            xPos = x;
            yPos = y;
        }
        void move(std::vector<Predator> &predatorsVector, std::vector<Food> &foodVector) {
            int lowest_predator_x = 0;
            int lowest_predator_y = 0;
            int lowest_food_x = 0;
            int lowest_food_y = 0;
            
            for (Predator predator : predatorsVector) {
                if (predator.get_y_pos() > lowest_predator_y) {
                    lowest_predator_x = predator.get_x_pos();
                    lowest_predator_y = predator.get_y_pos();
                }
            }
            for (Food food : foodVector) {
                if (food.get_y_pos() > lowest_food_y) {
                    lowest_food_x = food.get_x_pos();
                    lowest_food_y = food.get_y_pos();
                }
            }

            if (lowest_predator_y > lowest_food_y) {
                if (lowest_predator_x >= field_width / 2 && xPos > 0) {
                    xPos--;
                } else if (lowest_predator_x < field_width / 2 && xPos < field_width - 1) {
                    xPos++;
                }
            } else {
                if (lowest_food_x > xPos) {
                    xPos++;
                } else if (lowest_food_x < xPos) {
                    xPos--;
                }
            }
        }
};

int main() {
    std::system("clear");

    int food_eaten = 0;

    Creature creature (5, field_height - 1);

    std::vector< Food > foodVector;
    foodVector.push_back(Food( 3, 0));

    std::vector< Predator > predators;
    predators.push_back(Predator(5, 2));

    for (int y = 0; y < 22; y++) {
        cout << "_";
    }
    cout << endl;

    for (int r = 0; r < 1000; r++) {
        if (rand() % 12 == 0) {
            predators.push_back( Predator (rand() % field_width, 0) );
        }
        if (rand() % 10 == 0) {
            foodVector.push_back( Food (rand() % field_width, 0) );
        }

        std::system("clear");
        for (int y = 0; y < field_height; y++) {
            cout << "|";
            for (int x = 0; x < field_width; x++) {
                int outputFlag = false; 
                for (Predator predator : predators) {
                    if (x == predator.get_x_pos() && y == predator.get_y_pos()) {
                        cout << "P ";
                        outputFlag = true;
                    }
                }
                for (Food food : foodVector) {
                    if (x == food.get_x_pos() && y == food.get_y_pos()) {
                        cout << "F ";
                        outputFlag = true;
                    }
                }

                if (!outputFlag) {
                    if (x == creature.get_x_pos() && y == creature.get_y_pos()) {
                        cout << "C ";
                    } else {
                        cout << "  ";
                    }
                }
            }
            cout << "|" << endl; 
        }

        for (Predator predator : predators) {
            if (predator.get_x_pos() == creature.get_x_pos() && predator.get_y_pos() == creature.get_y_pos()) {
                cout << endl << "Food eaten: "<< food_eaten << endl;
                cout << "Creature died!" << endl;
                return false;
            }
        }

        for (Food food : foodVector) {
            if (food.get_x_pos() == creature.get_x_pos() && food.get_y_pos() == creature.get_y_pos()) {
                food_eaten++;                
            }
        }

        for (int a = 0; a < foodVector.size(); a++) {
            if (!foodVector[a].move_down()) {
                foodVector.erase(foodVector.begin() + a);
            }
        }

        for (int a = 0; a < predators.size(); a++) {
            if (!predators[a].move_down()) {
                predators.erase(predators.begin() + a);
            }
        }
        
        /*
        cout << endl << "Creature x: "<< creature.get_x_pos() << ", y: " << creature.get_y_pos() << endl;
        cout << endl << "Predator x: "<< predators[0].get_x_pos() << ", y: " << predators[0].get_y_pos() << endl;
        cout << endl << "Food x: "<< foodVector[0].get_x_pos() << ", y: " << foodVector[0].get_y_pos() << endl;
        */
        cout << endl << "Food eaten: "<< food_eaten << endl;
        cout << rand() % 10 << endl;
        // Varför blir det samma resultat varje gång???

        creature.move(predators, foodVector);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
