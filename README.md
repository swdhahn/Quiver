# Quiver
Object-oriented programming language very similar to java and cpp.

Basic Hello World Program:
```Quiver
class Main {

    int32 main() {
        
        println("Hewo world!");
        
        return 1;
    }

}
```
Slightly more advanced program:

```Quiver
class Animal {

    int32 health;
    float32 x, y;
    
    Animal(int32 health, float32 x, float32 y) {
        this.health = health;
        this.x = x;
        this.y = y;
    }
}

class Cat : Animal {

    void jump(float32 height) {
        this.y += height;
    }

}

class Main {

    int32 main() {
    
        Animal cat = new Cat(100, 25, 23);
        cat.jump(42);
        
        println("Cat's height: " + cat.y);
        
        return 1;
    }

}
```
Variable Types:
```Quiver
int16 num0 = 123; // short in c++, 16 bits
int32 num1 = 1234; // int in other languages, 32 bits
int64 num2 = 12345; // long in other languages, 64 bits

// unsigned numbers cannot be negative, instead they can reach much bigger positive numbers
uint16 num3 = 123; // unsigned short in c++, 16 bits
uint32 num4 = 1234; // unsigned int in other languages, 32 bits
uint64 num5 = 12345; // unsigned long in other languages, 64 bits

float32 num6 = 123.4; // float in other languages, 32 bits
float64 num7 = 123.45; // double in other languages, 64 bits

boolean condition = true; // either true/false or 1/0

string text = "hewo!"; // just a normal string
char character = 'h'; // single character

type* name = 0xFFFFFFFF; // Pointers for all types
```