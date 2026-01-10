println("Loading util.js...");

const PI = 3.14159;

function add(a, b) {
    return a + b;
}

function area(r) {
    return PI * r * r;
}

// 导出模块内容
export {
    add,
    area,
    PI
};
