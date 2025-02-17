#include <iostream>

class Enemy;

class Entity {
    private:
        std::string name;
        int health;
        int maxHealth;

    protected:
        int generateDamage() const;
    public:
        Entity(const std::string& name, int health) : name(name), health(health), maxHealth(health) {};

        void activeCombat(Enemy& enemy);

        virtual void attack(Entity& target);

        void takeDamage(int damage);

        int getHealth();

        void setHealth(int newHealth);

        int getMaxHealth() const;

        std::string getName() const;

        bool isAlive() const;

        void displayHealthBar() const;

    };

    class Player : public Entity {
        public:
            Player(const std::string& name) : Entity(name, 100) {}
    };

    class Enemy : public Entity {
        public:
            Enemy(const std::string& name) : Entity(name, 50) {}
    };