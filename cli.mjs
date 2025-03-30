import { Command } from "commander";
import chalk from 'chalk';
import inquirer from "inquirer";
import fs from "node:fs";
import readline from 'readline';
// import { pm } from './src/utilities/mdkpm';
import { assert } from "node:console";

const program = new Command();
const versionFile = "0.1.0"
const infoFile = 'info.mdk.yml'

function mdkrepl() {
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout
      });
      
      function evaluateInput(input) {
        try {
          const result = eval(input);
          return result;
        } catch (err) {
          return `Error: ${err.message}`;
        }
      }
      
      function startRepl() {
        rl.question('>>> ', (input) => {
          if (input.toLowerCase() === '.quit') {
            console.log('Goodbye!');
            rl.close();
            return;
          } else if (input.toLocaleLowerCase() == '.help') {
            console.log(`\
                .run <file> - Run a tookit specific file
                .call(name) - call a external function
                .js(<code>) - inject JavaScript code to run
                .c(<code>)  - inject C code to compile and run (requires gcc)
                .quit       - Exit the program
                `)
          } else if (input.toLocaleLowerCase() == '.run ${name}') {
          /*  const name = input.match($,{input})
            if (name.toLocaleLowerCase() == 'mdkpm') {
                function mdkpm() {
                    const man = new pm();

                    pm.init(mdk);

                    pm.parseCommand("add"); {
                        const currentCommand = pm.add();
                        pm.execute(currentCommand);
                    }

                    pm.parseCommand("remove"); {
                        const newCurrentCommand = pm.del();
                        pm.execute(newCurrentCommand);
                    }
                }
            } else {
                console.log(chalk.bold.red("Invalid input"));
            } */
          }
      
          const result = evaluateInput(input);
          console.log(result);
      
          // Re-prompt for more input
          startRepl();
        });
      }
      console.log(chalk.bold('Welcome to MDK repl!'))
      console.log('Type `.help` to see avaible commands.')
      startRepl();
}

program.version(versionFile)
    program.description("An cli application to automate the usage of MDK")
    program.helpCommand(true)
    program.command('init')
        //.description()
        .action(function() {
            fs.readFile(infoFile, 'w', function (err, file) {
                if (err) throw err;
                fs.writeFile(infoFile, `\
                    name: ${projName}
                    version: ${projVersion}

                    # dependencies:
                    #    powr: ^0.2.1

                    mdk:
                        version: 0.4
                        classic: ${isClassic}
                    `, function (err) {
                        if (err) throw err;
                    })
                fs.writeFile('main.pwr', `\
                    func {"main"
                        i* "libmdk"

                        mdk.init(main0)
                        func {"main0"
                            println("Hello from MDK %mdk.version!")
                            exit 0
                        }
                    }
                    `, function (err) {
                        if (err) throw err;
                    })
                console.log(chalk.green("Done."));
            })
        });

    program.command('rplf')
        .description('Start a MDK repl')
        .action(function() {
            mdkrepl();
        });
program.parse(process.argv);