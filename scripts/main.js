// 单行注释测试
/*
    多行注释测试
*/
import {add, PI} from "util.js";

println("2 + 3 = " + add(2, 3));
println("PI = " + PI);

let str = "Hello, ";

function greet(name) {
    return str + name + "!";
}

println(greet("World"));

var str = "Count: ";
for (var i = 0; i < 5; i++) {
    println(str + "(" + i + ")");
}

// str = "当前时间戳=" + now();
// print(str);
//
// var list = [1, 2, 3];
// print(list);
//
// list[0] = "hello";
// print(list[0]);

// class Person {
//     constructor(name, age) {
//         this.name = name;
//         this.age = age;
//     }
//
//     introduce() {
//         return "My name is " + this.name + " and I am " + this.age + " years old.";
//     }
// }
//
// var alice = new Person("Alice", 30);
// print(alice.introduce());