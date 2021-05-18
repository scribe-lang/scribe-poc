let io = @import("std/io");

let main = fn() {
	let a: [10]i32;
	for let i = 0; i < 10; ++i {
		a[i] = i * i;
	}
	for let i = 0; i < 10; ++i {
		io.println(a[i]);
	}
};