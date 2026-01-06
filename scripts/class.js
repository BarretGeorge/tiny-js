class Person {
    constructor(name) {
        this.name = name;
    }

    say() {
        print("I am " + this.name);
    }
}

var p = Person("Developer");
p.say();

p.name = "Engineer";
p.say();