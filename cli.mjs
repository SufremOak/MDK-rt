import { Command } from "commander";
import chalk from 'chalk';
import inquirer from "inquirer";
import fs from "node:fs";
import readline from 'readline';

const program = new Command();
const versionFile = "./version"
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
          if (input.toLowerCase() === 'exit') {
            console.log('Goodbye!');
            rl.close();
            return;
          }
      
          const result = evaluateInput(input);
          console.log(result);
      
          // Re-prompt for more input
          startRepl();
        });
      }
      console.log(chalk.bold('Welcome to MDK repl!'))
      console.log('Type `.help` to see avaible commands.')
}

program
    .version(versionFile)
    .description("An cli application to automate the usage of MDK")
    .helpCommand(true)
    .command('init')
        .description()
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
            startRepl();
        });
program.parse(process.argv);