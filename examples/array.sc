let io = @import("std/io");

let main = fn() {
	let a: *i32 = @array(:i32, 10);
	for let i = 0; i < 10; ++i {
		a[i] = i * i;
	}
	for let i = 0; i < 10; ++i {
		io.println(a[i]);
	}
};