# Build System

Small Bash-based scaffolding tool to create a C project from a template.

## What It Does

- Prompts you to select a template from `templates/`.
- Copies the template into a new project directory.
- Replaces the `PROJECTNAME` placeholder in filenames and file contents.

## Templates

- `default_C`: Minimal C project with a `Makefile`, `PROJECTNAME.C`, and `PROJECTNAME.H`.

## Usage

```bash
./bashbs.sh <project_name>
```

Example:

```bash
./bashbs.sh my_app
```

## Requirements

- Bash
- `perl` is optional. If not installed, `sed` is used for placeholder replacement.

## Notes

Run the script from the `Build System` directory so the output project is created beside it.
