function add(a, b) {
    return a + b;
}

function subtract(a, b) {
    return a - b;
}

function multiply(a, b) {
    return a * b;
}

function divide(a, b) {
    return a / b;
}

println("add(2, 3) = " + add(2, 3));
println("subtract(5, 2) = " + subtract(5, 2));
println("multiply(4, 6) = " + multiply(4, 6));
println("divide(10, 2) = " + divide(10, 2));

let factorial = (a) => {
    if(a <= 1) return 1;
    let total = 1;
    for (let i = 1; i <= a; i++) {
        total *= i;
    }
    return total;
}
println("factorial(10) = " + factorial(10));

let sum = 0;
for (let i = 0; i < 1000; i++) {
    sum += 1;
}
println("sum=" + sum);
sum *= 2;
println("sum=" + sum);
sum /= 4;
println("sum=" + sum);
sum -= 10;
println("sum=" + sum);
