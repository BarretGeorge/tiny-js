print("Loading math.js...");

const PI = 3.14159;

function add(a, b) {
    return a + b;
}

function area(r) {
    return PI * r * r;
}

const exports = [add, area];
return exports;