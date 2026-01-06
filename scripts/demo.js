// let util = require("util.js");
//
//
// let add = util[0];
//
// print("2 + 3 = " + add(2, 3));

let ts = 100;

print("ts= " + ts);

ts = 101;

print(ts);

print(now());

function hello() {
    print("Hello, World!");
}

hello();


class Person {
    init(name) {
        this.name = name;
    }

    sayHello() {
        print("Hello, I am " + this.name);
    }
}