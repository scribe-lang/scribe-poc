let puts = extern[puts, "<stdio.h>"] fn(data: *const i8): i32;

let cstr in i32 = fn(): *const i8 {
	return "null";
};

let puts = fn<T>(data: &T): i32 {
	return puts(data.cstr());
};

let print = fn(data: ...&any): i32 {
	let comptime valen = @va_len();
	let res = 0;
	inline for let comptime i = 0; i < valen; ++i {
		res += puts(data[i]);
	}
	return res;
};