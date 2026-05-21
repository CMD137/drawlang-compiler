import json
import sys
from pathlib import Path

import matplotlib

# Use the non-interactive backend so the script only writes files.
matplotlib.use("Agg")

import matplotlib.pyplot as plt
from matplotlib.patches import Circle, Rectangle

WIDTH = 800
HEIGHT = 600
VALID_COLORS = {
    "black",
    "white",
    "red",
    "green",
    "blue"
}


class BackendError(Exception):
    pass


def load_ir(input_path: Path) -> list[dict]:
    try:
        ir = json.loads(input_path.read_text(encoding="utf-8"))
    except FileNotFoundError as exc:
        raise BackendError(f"IR file not found: {input_path}") from exc
    except json.JSONDecodeError as exc:
        raise BackendError(f"Invalid JSON: {exc}") from exc

    commands = ir.get("commands")
    if not isinstance(commands, list):
        raise BackendError("IR field 'commands' must be a list")
    return commands


def check_ir(commands: list[dict]) -> list[dict]:
    checked = []
    for index, command in enumerate(commands, start=1):
        if not isinstance(command, dict):
            raise BackendError(f"Command {index}: must be an object")
        # Normalize and reject bad values before rendering.
        checked.append(check_command(command, index))
    return checked


def validate_ir(commands: list[dict]) -> list[dict]:
    return check_ir(commands)


def check_command(command: dict, index: int) -> dict:
    try:
        command_type = command["type"].lower()
    except KeyError as exc:
        raise BackendError(f"Command {index}: missing field {exc.args[0]!r}") from exc

    if command_type == "line":
        return check_line(command, index)
    if command_type == "rect":
        return check_rect(command, index)
    if command_type == "circle":
        return check_circle(command, index)
    if command_type == "text":
        return check_text(command, index)
    raise BackendError(f"Command {index}: unknown command type {command['type']}")


def check_line(command: dict, index: int) -> dict:
    try:
        x1 = read_number(command["x1"], index, "x1")
        y1 = read_number(command["y1"], index, "y1")
        x2 = read_number(command["x2"], index, "x2")
        y2 = read_number(command["y2"], index, "y2")
        color = read_color(command["color"], index, "color")
        line_width = read_positive_number(command["lineWidth"], index, "lineWidth")
    except KeyError as exc:
        raise BackendError(f"Command {index}: missing field {exc.args[0]!r}") from exc

    ensure_point(x1, y1, index, "line start point")
    ensure_point(x2, y2, index, "line end point")
    return {
        "type": "line",
        "x1": x1,
        "y1": y1,
        "x2": x2,
        "y2": y2,
        "color": color,
        "lineWidth": line_width,
    }


def check_rect(command: dict, index: int) -> dict:
    try:
        x = read_number(command["x"], index, "x")
        y = read_number(command["y"], index, "y")
        width = read_positive_number(command["width"], index, "width")
        height = read_positive_number(command["height"], index, "height")
        color = read_color(command["color"], index, "color")
        line_width = read_positive_number(command["lineWidth"], index, "lineWidth")
        fill = read_optional_color(command["fill"], index, "fill")
    except KeyError as exc:
        raise BackendError(f"Command {index}: missing field {exc.args[0]!r}") from exc

    if x < 0 or y < 0 or x + width > WIDTH or y + height > HEIGHT:
        raise BackendError(f"Command {index}: rect out of canvas")
    return {
        "type": "rect",
        "x": x,
        "y": y,
        "width": width,
        "height": height,
        "color": color,
        "lineWidth": line_width,
        "fill": fill,
    }


def check_circle(command: dict, index: int) -> dict:
    try:
        cx = read_number(command["cx"], index, "cx")
        cy = read_number(command["cy"], index, "cy")
        radius = read_positive_number(command["radius"], index, "radius")
        color = read_color(command["color"], index, "color")
        line_width = read_positive_number(command["lineWidth"], index, "lineWidth")
        fill = read_optional_color(command["fill"], index, "fill")
    except KeyError as exc:
        raise BackendError(f"Command {index}: missing field {exc.args[0]!r}") from exc

    if cx - radius < 0 or cy - radius < 0 or cx + radius > WIDTH or cy + radius > HEIGHT:
        raise BackendError(f"Command {index}: circle out of canvas")
    return {
        "type": "circle",
        "cx": cx,
        "cy": cy,
        "radius": radius,
        "color": color,
        "lineWidth": line_width,
        "fill": fill,
    }


def check_text(command: dict, index: int) -> dict:
    try:
        x = read_number(command["x"], index, "x")
        y = read_number(command["y"], index, "y")
        content = command["content"]
        color = read_color(command["color"], index, "color")
        font_size = read_positive_number(command["fontSize"], index, "fontSize")
    except KeyError as exc:
        raise BackendError(f"Command {index}: missing field {exc.args[0]!r}") from exc

    if not isinstance(content, str) or content == "":
        raise BackendError(f"Command {index}: text content cannot be empty")
    ensure_point(x, y, index, "text point")
    return {
        "type": "text",
        "x": x,
        "y": y,
        "content": content,
        "color": color,
        "fontSize": font_size,
    }


def read_number(value: object, index: int, field_name: str) -> float:
    if not isinstance(value, (int, float)):
        raise BackendError(f"Command {index}: {field_name} must be a number")
    return float(value)


def read_positive_number(value: object, index: int, field_name: str) -> float:
    number = read_number(value, index, field_name)
    if number <= 0:
        raise BackendError(f"Command {index}: {field_name} must be positive")
    return number


def read_color(value: object, index: int, field_name: str) -> str:
    if not isinstance(value, str):
        raise BackendError(f"Command {index}: {field_name} must be a color string")
    color = value.lower()
    if color not in VALID_COLORS:
        raise BackendError(f"Command {index}: invalid color")
    return color


def read_optional_color(value: object, index: int, field_name: str) -> str | None:
    if value is None:
        return None
    return read_color(value, index, field_name)


def ensure_point(x: float, y: float, index: int, label: str) -> None:
    if x < 0 or x > WIDTH or y < 0 or y > HEIGHT:
        raise BackendError(f"Command {index}: {label} out of canvas")


def render(commands: list[dict], output_path: Path) -> None:
    fig, ax = plt.subplots(figsize=(8, 6), dpi=100)

    # Match the assignment's fixed canvas coordinates.
    ax.set_xlim(0, WIDTH)
    ax.set_ylim(HEIGHT, 0)
    ax.set_aspect("equal")
    ax.set_facecolor("white")
    ax.axis("off")

    for command in commands:
        command_type = command["type"]

        if command_type == "line":
            ax.plot(
                [command["x1"], command["x2"]],
                [command["y1"], command["y2"]],
                color=command["color"],
                linewidth=command["lineWidth"],
            )
        elif command_type == "rect":
            ax.add_patch(
                Rectangle(
                    (command["x"], command["y"]),
                    command["width"],
                    command["height"],
                    edgecolor=command["color"],
                    facecolor=command["fill"] if command["fill"] is not None else "none",
                    linewidth=command["lineWidth"],
                )
            )
        elif command_type == "circle":
            ax.add_patch(
                Circle(
                    (command["cx"], command["cy"]),
                    command["radius"],
                    edgecolor=command["color"],
                    facecolor=command["fill"] if command["fill"] is not None else "none",
                    linewidth=command["lineWidth"],
                )
            )
        elif command_type == "text":
            ax.text(
                command["x"],
                command["y"],
                command["content"],
                color=command["color"],
                fontsize=command["fontSize"],
                ha="left",
                va="top",
            )

    fig.savefig(output_path, bbox_inches="tight", pad_inches=0.1)
    plt.close(fig)


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        print("Usage: python draw_backend.py <input_ir.json>")
        return 1

    input_path = Path(argv[1]).resolve()
    output_path = input_path.with_suffix(".png")

    try:
        ir = load_ir(input_path)
        checked_ir = check_ir(ir)
        if checked_ir is not None:
            render(checked_ir, output_path)
        print(f"Image generated: {output_path}")
        return 0
    except BackendError as exc:
        print(f"[Semantic Error] {exc}")
        return 1


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
