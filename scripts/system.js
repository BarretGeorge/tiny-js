println("开始执行");


sleep(1000);

println("休眠结束");

setTimeout(function () {
    println("两秒后执行的代码");
}, 2000);

setTimeout(function () {
    println("三秒后执行的代码");
}, 3000);

let id = setInterval(function () {
    println("每秒执行一次的代码");
}, 1000);

setTimeout(function () {
    println("定时器已启动,id=" , id);
    clearInterval(id);
    println("停止定时器");
}, 3500);