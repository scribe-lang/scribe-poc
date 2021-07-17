let io = @import("std/io");
let vec = @import("std/vec");

// default return type = void
let main = fn() {
	let v = vec.new(:i32);
	for let i = 0; i < 20; ++i {
		v.push(i);
	}
	io.println("vector contents:");
	io.println("{}", v);
};