import { Command } from 'commander';
import { curly, Curl } from 'node-libcurl';
import { YAMLSet, YAMLError, YAMLOMap, YAMLMap } from 'yaml';
import { Path } from 'typescript';

const curl = new Curl();
const versionFile = "../version"
const program = new Command();
const version = versionFile

function packageMan() {
    program.name('mdkpm')
    program.version(version)
    program
        .command("add <package>")
        .description("Add a package to info.mdk.yml")
        .action(async function() {
            const { statusCode, data, headers } = await curly.get('http://www.github.com/sufremoak/mdkpm-mirror')

        });
        program.command("remove <package>")
                .description("Remove a package from info.mdk.yml")
                .action(function() {});     
}