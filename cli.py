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

if __name__ == "__main__":
    app()