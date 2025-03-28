import typer
import subprocess

from rich import print
from rich.console import Console

app = typer.Typer()
console = Console()

@app.command()
def list(help="Lists all MDK binaries"):
    print(f"[bold]MDK Binary list[/bold]")
    print(f"powrcc     Powr Compiler")
    print(f"mdkre      MDK's REPL/mini Shell")
    print(f"libutil    MDK Library manager")
    print(f"mdkpm      MDK package manager")
    print(f"aracc      Project ARA Powr target compiler")

@app.command()
def run(help="Run a mdk-toolkit binary")
    pass

if __name__ == "__main__":
    app()