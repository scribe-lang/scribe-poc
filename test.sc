let Vec = struct<T> {
	sz: u64;
	cap: u64;
	data: *T;
};

let make = fn<T>() {
	return Vec(:T, 0, 5, nil);
};

std.vec.make(:i32);

let push in Vec<T> = fn(item: T) {
	
};



push(:i32, 5);