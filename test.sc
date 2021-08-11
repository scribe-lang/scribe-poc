let tmp = @import("./tmp");

let a = tmp.Vec(:i32, 5);
let b = tmp.Map(5, '5');
tmp.f(a, b);