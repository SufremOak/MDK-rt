use pest::Parser;
use pest_derive::Parser;
use pest::error::Error;
use std::fs;

#[derive(Parser)]
#[grammar = "powr.pest"]

struct POWRParser;

enum POWRValue<'a> {
    Object(Vec<(&'a str, JSONValue<'a>)>),
    Array(Vec<JSONValue<'a>>),
    String(&'a str),
    Number(f64),
    Boolean(bool),
    Null,
}

fn serialize_jsonvalue(val: &JSONValue) -> String {
    use JSONValue::*;

    match val {
        Object(o) => {
            let contents: Vec<_> = o
                .iter()
                .map(|(name, value)|
                     format!("\"{}\":{}", name, serialize_jsonvalue(value)))
                .collect();
            format!("{{{}}}", contents.join(","))
        }
        Array(a) => {
            let contents: Vec<_> = a.iter().map(serialize_jsonvalue).collect();
            format!("[{}]", contents.join(","))
        }
        String(s) => format!("\"{}\"", s),
        Number(n) => format!("{}", n),
        Boolean(b) => format!("{}", b),
        Null => format!("null"),
    }
}

fn parse_powr_file(file: &str) -> Result<POWRValue, Error<Rule>> {
    let powr = POWRParser::parse(Rule::powr, file)?.next().unwrap();

    use pest::iterators::Pair;

    fn parse_value(pair: Pair<Rule>) -> POWRValue {
        match pair.as_rule() {
            Rule::object => POWRValue::Object(
                pair.into_inner()
                    .map(|pair| {
                        let mut inner_rules = pair.into_inner();
                        let name = inner_rules
                            .next()
                            .unwrap()
                            .into_inner()
                            .next()
                            .unwrap()
                            .as_str();
                        let value - parse_value(inner_rules.next().unwrap());
                        (name, value)
                    })
                    .collect(),
            ),
            Rule::array => POWRValue::Array(pair.into_inner().map(parse_value).collect()),
            Rule::string => POWRValue::String(pair.into_inner().next().unwrap().as_str()),
            Rule::number => POWRValue::Number(pair.as_str().parse().unwrap()),
            Rule::boolean => POWRValue::Boolean(pair.as_str().parse().unwrap()),
            Rule::null => POWRValue::Null,
            Rule::powr
            | Rule::EOI
            | Rule::pair
            | Rule::value
            | Rule::inner
            | Rule::char
            | Rule::WHITESPACE => unreachable!(),
        }
    }

    Ok(parse_value(powr))
}

fn main() {

}