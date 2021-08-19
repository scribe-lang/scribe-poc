// let st = struct {
// 	i: i32;
// 	u: *const u8;
// };

// let stvar = st(5, "hi");
// let x = stvar.i;
// let f = fn(i: i32, j: i32): i32 {
// 	return x;
// };
// if x {
// 	let a = 5;
// } else {
// 	let b = 10;
// }

let sum = 0;

inline for let comptime i = 0; i < 20; ++i {
	sum += i;
}