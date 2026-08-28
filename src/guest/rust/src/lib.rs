#[allow(warnings)]
mod bindings;

use bindings::exports::app::utility::info::Guest;

struct Component;

impl Guest for Component {
    fn get_message(number: i32) -> String {
        format!("This is Rust function, number = {}", number)
    }
}

bindings::export!(Component with_types_in bindings);
