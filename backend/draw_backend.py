import json
import sys
from pathlib import Path

WIDTH = 800
HEIGHT = 600
VALID_COLORS = {
    "black",
    "white",
    "red",
    "green",
    "blue",
    "yellow",
    "gray",
    "orange",
    "purple",
    "pink",
}


class BackendError(Exception):
    pass


def load_ir(path: Path) -> dict:
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except FileNotFoundError as exc:
        raise BackendError(f"IR file not found: {path}") from exc
    except json.JSONDecodeError as exc:
        raise BackendError(f"Invalid JSON: {exc}") from exc


def require_fields(command: dict, fields: list[str]) -> None:
    missing = [field for field in fields if field not in command]
    if missing:
        raise BackendError(f"Missing field(s) {missing} in command: {command}")


def validate_color(color: str) -> str:
    if not isinstance(color, str):
        raise BackendError(f"Color must be string, got: {color!r}")
    normalized = color.lower()
    if normalized not in VALID_COLORS:
        raise BackendError(f"Unsupported color: {color}")
    return normalized


def validate_number(value, field_name: str) -> float:
    if not isinstance(value, (int, float)):
        raise BackendError(f"Field '{field_name}' must be a number, got: {value!r}")
    return float(value)


def validate_positive(value, field_name: str) -> float:
    number = validate_number(value, field_name)
    if number <= 0:
        raise BackendError(f"Field '{field_name}' must be greater than 0, got: {value}")
    return number


def ensure_point_in_canvas(x: float, y: float, label: str) -> None:
    if not (0 <= x <= WIDTH and 0 <= y <= HEIGHT):
        raise BackendError(f"{label} out of canvas: ({x}, {y})")


def validate_ir(data: dict) -> list[dict]:
    if not isinstance(data, dict):
        raise BackendError("IR root must be an object")
    commands = data.get("commands")
    if not isinstance(commands, list):
        raise BackendError("IR field 'commands' must be a list")

    validated = []
    for command in commands:
        if not isinstance(command, dict):
            raise BackendError(f"Command must be object, got: {command!r}")
        validated.append(validate_command(command))
    return validated


def validate_command(command: dict) -> dict:
    cmd_type = command.get("type")
    if not isinstance(cmd_type, str):
        raise BackendError(f"Command type must be string, got: {cmd_type!r}")
    cmd_type = cmd_type.lower()

    if cmd_type == "line":
        require_fields(command, ["x1", "y1", "x2", "y2", "color", "lineWidth"])
        x1 = validate_number(command["x1"], "x1")
        y1 = validate_number(command["y1"], "y1")
        x2 = validate_number(command["x2"], "x2")
        y2 = validate_number(command["y2"], "y2")
        ensure_point_in_canvas(x1, y1, "Line start point")
        ensure_point_in_canvas(x2, y2, "Line end point")
        return {
            "type": "line",
            "x1": x1,
            "y1": y1,
            "x2": x2,
            "y2": y2,
            "color": validate_color(command["color"]),
            "lineWidth": validate_positive(command["lineWidth"], "lineWidth"),
        }

    if cmd_type == "rect":
        require_fields(command, ["x", "y", "width", "height", "color", "lineWidth", "fill"])
        x = validate_number(command["x"], "x")
        y = validate_number(command["y"], "y")
        width = validate_positive(command["width"], "width")
        height = validate_positive(command["height"], "height")
        ensure_point_in_canvas(x, y, "Rect top-left")
        ensure_point_in_canvas(x + width, y + height, "Rect bottom-right")
        fill = command["fill"]
        if fill is not None:
            fill = validate_color(fill)
        return {
            "type": "rect",
            "x": x,
            "y": y,
            "width": width,
            "height": height,
            "color": validate_color(command["color"]),
            "lineWidth": validate_positive(command["lineWidth"], "lineWidth"),
            "fill": fill,
        }

    if cmd_type == "circle":
        require_fields(command, ["cx", "cy", "radius", "color", "lineWidth", "fill"])
        cx = validate_number(command["cx"], "cx")
        cy = validate_number(command["cy"], "cy")
        radius = validate_positive(command["radius"], "radius")
        ensure_point_in_canvas(cx, cy, "Circle center")
        if cx - radius < 0 or cy - radius < 0 or cx + radius > WIDTH or cy + radius > HEIGHT:
            raise BackendError(f"Circle out of canvas boundary: center=({cx}, {cy}), radius={radius}")
        fill = command["fill"]
        if fill is not None:
            fill = validate_color(fill)
        return {
            "type": "circle",
            "cx": cx,
            "cy": cy,
            "radius": radius,
            "color": validate_color(command["color"]),
            "lineWidth": validate_positive(command["lineWidth"], "lineWidth"),
            "fill": fill,
        }

    if cmd_type == "text":
        require_fields(command, ["x", "y", "content", "color", "fontSize"])
        x = validate_number(command["x"], "x")
        y = validate_number(command["y"], "y")
        ensure_point_in_canvas(x, y, "Text point")
        content = command["content"]
        if not isinstance(content, str) or content == "":
            raise BackendError("Text content must be a non-empty string")
        return {
            "type": "text",
            "x": x,
            "y": y,
            "content": content,
            "color": validate_color(command["color"]),
            "fontSize": validate_positive(command["fontSize"], "fontSize"),
        }

    raise BackendError(f"Unknown command type: {cmd_type}")


def import_matplotlib():
    try:
        import matplotlib.pyplot as plt
        from matplotlib.patches import Circle, Rectangle
        return plt, Circle, Rectangle
    except ModuleNotFoundError as exc:
        raise BackendError(
            "matplotlib is not installed. Run: python -m pip install matplotlib"
        ) from exc


def configure_fonts(plt) -> None:
    plt.rcParams["font.sans-serif"] = [
        "Microsoft YaHei",
        "SimSun",
        "SimHei",
        "Arial Unicode MS",
    ]
    plt.rcParams["axes.unicode_minus"] = False


def draw(commands: list[dict], output_path: Path) -> None:
    plt, CirclePatch, RectanglePatch = import_matplotlib()
    configure_fonts(plt)

    fig, ax = plt.subplots(figsize=(8, 6), dpi=100)
    ax.set_xlim(0, WIDTH)
    ax.set_ylim(HEIGHT, 0)
    ax.set_aspect("equal")
    ax.set_facecolor("white")
    ax.axis("off")

    for command in commands:
        cmd_type = command["type"]
        if cmd_type == "line":
            ax.plot(
                [command["x1"], command["x2"]],
                [command["y1"], command["y2"]],
                color=command["color"],
                linewidth=command["lineWidth"],
            )
        elif cmd_type == "rect":
            patch = RectanglePatch(
                (command["x"], command["y"]),
                command["width"],
                command["height"],
                linewidth=command["lineWidth"],
                edgecolor=command["color"],
                facecolor=command["fill"] if command["fill"] is not None else "none",
            )
            ax.add_patch(patch)
        elif cmd_type == "circle":
            patch = CirclePatch(
                (command["cx"], command["cy"]),
                command["radius"],
                linewidth=command["lineWidth"],
                edgecolor=command["color"],
                facecolor=command["fill"] if command["fill"] is not None else "none",
            )
            ax.add_patch(patch)
        elif cmd_type == "text":
            ax.text(
                command["x"],
                command["y"],
                command["content"],
                color=command["color"],
                fontsize=command["fontSize"],
                va="top",
                ha="left",
            )

    output_path.parent.mkdir(parents=True, exist_ok=True)
    fig.savefig(output_path, bbox_inches="tight", pad_inches=0.1)
    plt.close(fig)


def main(argv: list[str]) -> int:
    if len(argv) != 3:
        print("Usage: python backend\\draw_backend.py <input_ir.json> <output.png>")
        return 1

    input_path = Path(argv[1])
    output_path = Path(argv[2])

    try:
        data = load_ir(input_path)
        commands = validate_ir(data)
        draw(commands, output_path)
        print(f"PNG generated: {output_path}")
        return 0
    except BackendError as exc:
        print(f"[Backend Error] {exc}")
        return 1


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
