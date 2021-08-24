let c_allocate = extern[malloc, "<stdlib.h>"] fn(size: u64): *void;
let c_reallocate = extern[realloc, "<stdlib.h>"] fn(data: *void, newsz: u64): *void;
let c_free = extern[free, "<stdlib.h>"] fn(data: *void);

let malloc = fn<T>(count: u64): *T {
	let comptime sz = @sizeof(:T);
	return @as(:*T, c_allocate(sz * count));
};

let realloc = fn<T>(data: *T, count: u64): *T {
	return @as(:*T, c_reallocate(@as(:*void, data), count));
};

let free = fn<T>(data: *T) {
	c_free(@as(:*void, data));
};