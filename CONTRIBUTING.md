# Contribution Guidelines

## GitHub Flow

Utilize GitHub Issues and GitHub Projects for efficient project management.

1. **Self-assign an issue:** Take ownership of an issue before starting work.
2. **Create a new branch:** Work on the issue within a new branch.
3. **Pull Request creation:** Open a pull request (with a descriptive title, e.g.: "Implement SP AST", description of functional changes, screenshots/logs if necessary), mentioning the related issue and specifying whether it can close the issue.
4. **Code review request:** Request a code review from relevant stakeholders.
5. **Squash/rebase and merge:** After approval, you (not the reviewers) are responsible to squash/rebase and merge your changes, then delete the branch.
6. **Close the issue:** If applicable, mark the issue as completed.

## Branch Naming Conventions

Follow these conventions for clear branch identification:

- Branch names should be lowercase and hyphen-delimited.
- Be concise and descriptive (e.g., `feat/add-processing-component`).
- Use the following prefixes:
  - `pkb/` | `sp/` | `qps/`: Work done on the respective subsystems.
  - `i9n/`: Cross-subsystem work.
  - `fix/`: Fixing bugs.
  - `test/`: Writing tests.
  - `chore/`: Working on non-functional components, such as config files.
  - `doc/`: Updating documentation.

## Code Editor Setup

Ensure the following configurations:

- **Automatic code formatting:** Use the included `.clang-format` file for autoformatting.
- **Single new line at the end:** Ensure there's an automatic single new line at the end of source code files.

Consider enabling formatting on save, storing settings locally (check if `.gitignore`d) to avoid committing them to the remote repository.

Thank you, and happy contributing!

## Naming Conventions

- Class Names, Header Files, CPP Files: UpperCamelCase
- Directories
  - PKB/QPS/SP: UPPERCASE and keep as is
  - If directory has a main controller class in it with same name: UpperCamelCase
  - If directory does not have a main controller class in it: lowercase
  - Else: lowercase

## Directory Structure

- Parent component folders (PKB, QPS, SP)
  - Subcomponents (Tokenizer, Parser, Syntax, etc.)
    - include
      - follow same structure as src folder in same nesting level
    - src
      - further subcomponent division
  - include
    - follow same structure as src folder in same nesting level
  - src
    - other classes
