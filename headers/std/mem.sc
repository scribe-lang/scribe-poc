let c_allocate = extern[malloc, "<stdlib.h>"] fn(size: u64): *void;
let c_free = extern[free, "<stdlib.h>"] fn(data: *void);

let malloc = fn<T>(count: u64): *T {
	let comptime sz = @sizeof(:T);
	return @as(:*T, c_allocate(sz * count));
};

let free = fn<T>(data: *T) {
	c_free(@as(:*void, data));
};