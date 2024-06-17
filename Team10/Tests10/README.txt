The test files are split into their respective sprints i.e Sprint 1, Sprint 2.
Within these folders, there is a "sources" and a "queries" folder.

Inside the "sources" folder, there are the source programs for our test cases. There is also a folder called "sourcesWithStmt#" which stores the large source programs but with statement number comments for easier test creation and debugging.
Inside the "queries" folder, there are multiple folders that are named after these source programs with multiple queries files within it.
These queries files will be used to test their respective source programs.

To easily run these test cases, a shell script is created called "runTest.sh"
Running the shell script does the follow:
    - Clears the output folder before each run.
    - Iterates through each source file in the Sprint2/sources folder. It does not go into subfolders
    - For each source file, finds corresponding query files in the subfolder with the same name in the Sprint2/queries folder. For example source/valid_1_source.txt and queries/valid_1_source
    - Executes the autotester tool for each combination of source and query files, producing XML output files in the output folder.
    - Starts a Python HTTP server on port 8000 to serve the XML output files.
    - Opens the default web browser to view the generated XML files using localhost.
