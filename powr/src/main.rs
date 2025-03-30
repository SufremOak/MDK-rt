use pest::Parser;
use pest_derive::Parser;
use std::collections::HashMap;
use std::fs;
use std::process::Command;
use std::env;

#[derive(Parser)]
#[grammar = "powr.pest"]
struct POWRParser;

#[derive(Debug)]
struct Interpreter {
    variables: HashMap<String, String>,
}

impl Interpreter {
    fn new() -> Self {
        Interpreter {
            variables: HashMap::new(),
        }
    }

    fn run(&mut self, input: &str) {
        let parsed = POWRParser::parse(Rule::program, input).expect("Parsing failed");

        for pair in parsed {
            match pair.as_rule() {
                Rule::main_declaration => self.execute_main(pair),
                Rule::statement => self.execute_statement(pair),
                _ => unreachable!(),
            }
        }
    }

    fn execute_main(&mut self, pair: pest::iterators::Pair<Rule>) {
        // Handle main function execution
        for statement in pair.into_inner() {
            self.execute_statement(statement);
        }
    }

    fn execute_statement(&mut self, pair: pest::iterators::Pair<Rule>) {
        match pair.as_rule() {
            Rule::print_statement => {
                let message = pair.into_inner().next().unwrap().as_str();
                println!("{}", message);
            }
            Rule::variable_declaration => {
                let mut inner = pair.into_inner();
                let var_name = inner.next().unwrap().as_str().to_string();
                let value = inner.next().unwrap().as_str().to_string();
                self.variables.insert(var_name, value);
            }
            Rule::if_statement => {
                let mut inner = pair.into_inner();
                let condition = inner.next().unwrap();
                let condition_result = self.evaluate_expression(condition);
                if condition_result {
                    for statement in inner {
                        self.execute_statement(statement);
                    }
                }
            }
            Rule::else_statement => {
                // Handle else statement logic
                for statement in pair.into_inner() {
                    self.execute_statement(statement);
                }
            }
            Rule::try_statement => {
                let mut inner = pair.into_inner();
                let try_block = inner.next().unwrap();
                let catch_block = inner.next().unwrap();
                // Execute try block
                if let Err(_) = std::panic::catch_unwind(|| {
                    self.execute_try_block(try_block);
                }) {
                    // Execute catch block
                    for statement in catch_block.into_inner() {
                        self.execute_statement(statement);
                    }
                }
            }
            Rule::function_definition => {
                // Implement function definition logic
                let mut inner = pair.into_inner();
                let func_name = inner.next().unwrap().as_str().to_string();
                // Store the function definition in a map or execute immediately
                // For simplicity, we can just print the function name
                println!("Function defined: {}", func_name);
            }
            Rule::file_check => {
                let file_name = pair.into_inner().next().unwrap().as_str();
                if fs::metadata(file_name).is_err() {
                    println!("File not found!");
                } else {
                    Command::new("powr").arg(file_name).status().expect("Failed to execute command");
                }
            }
            _ => unreachable!(),
        }
    }

    fn execute_try_block(&self, try_block: pest::iterators::Pair<Rule>) {
        for statement in try_block.into_inner() {
            self.execute_statement(statement);
        }
    }

    fn evaluate_expression(&self, pair: pest::iterators::Pair<Rule>) -> bool {
        // Implement logic to evaluate expressions
        // For now, return true for demonstration purposes
        true
    }
}

fn main() {
    // Get the command-line arguments
    let args: Vec<String> = env::args().collect();

    // Check if a file path was provided
    if args.len() < 2 {
        eprintln!("Usage: powr <path_to_powr_file>");
        std::process::exit(1);
    }

    let file_path = &args[1];
    let input = fs::read_to_string(file_path).expect("Unable to read file");
    
    // Debugging output to see the raw input
    println!("Input from file:\n{}", input);
    
    let mut interpreter = Interpreter::new();
    interpreter.run(&input);
}