let Box = struct<T> {
	d: T;
};

let factor = 10;

let func = comptime fn<T>(e: ...Box<T>): i32 {
	return (e[0].d + e[1].d) * factor;
};

let a = Box(5);
let b = Box(10);

let r = func(:i32, a, b);