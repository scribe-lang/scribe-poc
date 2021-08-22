let test = @import("./a");

let comptime n = test.x;

let stinst = test.st(5, "hi");

let comptime x = test.stvar.i;

let p = "200";
let comptime q = p[1];

let sum = fn(a: &const i32, b: &const i32): i32 { return a + b; };

let main = fn(argc: i32, argv: **i8): i32 {
	let a = 1, b = 2;
	let c: &i32 = a;
	return sum(a, b);
};