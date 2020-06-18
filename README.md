# AVCGroupProject
<h3>Group Plan for ENGR101 AVC Project</h3> <br>
                                       

<h3>Team Name: TBD</h3> <br>
<h3>Team Members & contact info:</h3> <br>
<b>Hunter Arthur</b> - arthurhunt@myvuw.ac.nz<br>
<b>Jamuel Bocacao</b> - bocacajamu@vuw.ac.nz <br>
<b>Jeffrey Peake</b> - peakejeff@myvuw.ac.nz <br>
<b>James Ybanez</b> - ybanezjame@vuw.ac.nz <br>

<b>Communication tool:</b> <br>
Discord <br>

Roles: <br>
Jamuel Bocacao - Project Manager (organising team meetings, reporting regularly on progress) <br>

Jeffrey Peake - Software Architect (writing core code and extending functionality) <br>

Hunter Arthur - Software writing, testing and documentation (debugging software and committing to
git, writing test cases and documenting performance against milestones) <br>

James Ybanez - Software writing, testing and documentation (debugging software and committing to 
git, writing test cases and documenting performance against milestones) <br>

<h4> " * " Denotes that it has the same value above it </h4> <br>

| Date Comp.     | Objectives                             | Due Date               | Item Due                        | Tasks                                                               | Member Involvement |
|----------------|----------------------------------------|------------------------|---------------------------------|---------------------------------------------------------------------|--------------------|
| 3rd June <br> * <br> 9th June               | Preparing the project                  | 4th June               | N/A                             | Assign Roles and Tasks<br>Installation of software<br>Test software | All                |
| 2nd June       | *                                      | *                      | Group Github link               | Create group github                                                 | Project Manager    |
| 3rd June       | *                                      | *                      | Group Plan                      | Completed Plan                                                      | All                |
| 11th June      | Coding the robot                       | 12th June              | Robot Code                      | Design Core Code<br>Testing Code                                    | Jeffrey Peake<br> James Ybanez|
| 15th June      | *                                      | 15th June              | *                               | Adapt Code to Completion Standards<br>Testing Code                  | Hunter Arthur<br> James Ybanez|
| 17th June      | *                                      | 18th June              | *                               | Adapt Code to Challenge Standards<br>Testing Code                   | Jamuel Bocacao     |
| *              | Testing robot                          | 19th June              | N/A                             | Test Robot in Maze<br>Debug Robot                                   | All                |
| 11th June <br> 17th June| Week 1 Discussion<br>Week 2 Discussion | 12th June<br>19th June | Report of weekly<br>discussions | Write a log showing the progress report of project every week       | Project Manager    |


<br><h1>Installation for Windows 64 Bit PCs</h1><br>
<h2> Prerequisites </h3><br>

<b> Before installing the robot program, we have to download the compiler and libraries </b><br>

<h3> Compiler </h3><br>
<p>1. First <b>download</b> the <a href="https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-posix/seh/x86_64-7.3.0-release-posix-seh-rt_v5-rev0.7z/download">compiler</a></p>
<p>2. Once its finished downloading, <b>unzip</b> the file, and <b>open</b> the <b>mingw64</b> folder</p>
<p>3. <b>Copy</b> the <b>contents</b> of the <b>mingw64</b> folder into a folder called <b>MinGW</b> in your main drive (typically C:)</p>
<p> Your folder should look like this </p>
<img src="https://raw.githubusercontent.com/Team5-AVC-Project/AVC_Project/Challenge/MinGW%20folder.PNG"></img>
<p>4. Enter the <b>bin folder<> and <b>copy</b> its <b>directory</b> (e.g. C:\MinGW\bin)</p>
<p>5. Next go to your <b>environment variables</b> </p>
* In <b>Windows 8 and 10</b>, this can be done by going into <b>search<b> and <b>looking up "Environment Variables"</b> </p>
* In <b>Windows 7</b>. this can be done by going into <b>Control panel > System and Security > System > Advanced Settings > Environment Variables</b> </p>
<p>6. <b>Edit</b> your <b>Path</b> Variables so that it <b>contains</b> the <b>directory</b> of the <b>compiler bin</b> folder
  
<h3> SFML Libraries </h3><br>
<p>1. First <b>download</b> the <a href="https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip">SFML Library</a></p>
<p>2. Once its finished downloading, <b>unzip</b> the file, and open the <b>SFML-2.5.1 Folder</b></p>
<p>3. <b>Copy</b> the contents of the <b>SFML-2.5.1</b> folder into a folder called <b>SFML</b> in your main drive (typically C:)</p>
<p> Your folder should look like this </p>
<img src="https://github.com/Team5-AVC-Project/AVC_Project/blob/Challenge/MinGW%20folder.PNG"></img>

<br><h2>Installing Robot Files</h2><br>
<p>1. First <b>download</b> the <b>AVC_WIN10</b> zip file</p>
<p>2. Once its finished downloading, <b>unzip</b> the file, and open the <b>AVC_WIN10 Folder</b></p>
<p>3. <b>Go into</b> your <b>SFML folder</b> and enter the <b>bin folder</b></p>
<p>4. <b>Copy all</b> of the <b>contents inside</b> the folder and <b>paste</b> them into the <b>AVC_robot folder</b> and the <b>AVC_server folder</b></p>
<img src="https://github.com/Team5-AVC-Project/AVC_Project/blob/master/SFMLBin.PNG"></img>
<p>5. <b>Delete</b> the <b>robot.exe, robot.o, server3.exe, and server.o files</b> from their folders</p>
<p>6. <b>Go into Geany</b>, click <b>build</b> in the uppermost toolbar, click on <b>Set Build Commands</b></p>
<p>7. Change the <b>make command to mingw32-make</b></p>
<p>Your build commands should look like this </p>
<img src="https://github.com/Team5-AVC-Project/AVC_Project/blob/master/Build%20Commands.PNG"></img><br>
<p>8. <b>Download</b> the <b>robot.cpp</b> file from the repository and put it into the <b>AVC_robot folder</b></p>
<h3> IMPORTANT </h3>
<p>If your <b>SFML folder directory</b> does <b>not</b> look like this <b>(C:\SFML)</b> when installing the libraries, <b>go</b> into the <b>makefiles</b> of both the <b>robot</b> and the <b>server</b> folders, and <b>change</b> the <b>code</b> at the <b>top line</b> to whatever <b>directory</b> your <b>folder</b> has, <b>INCLUDE</b> an <b>extra \</b> after <b>C:\</b></p>
<p>The <b>directory</b> of the <b>folder</b> can be accessed by <b>clicking</b> on the <b>address bar<b> containing the text <b>(.../>SFML)</b></p>
<p>9. Open the <b>robot.cpp</b> file, and the <b>server3.cpp</b> file, for <b>each file</b>, go into <b>build</b>, and click <b>make</b></p>

<br><h2>Running Program</h2><br>
* To choose the maze to run, enter config.txt, there are three mazes to choose from (core.txt, completion.txt, challenge.txt) remove the core.txt and replace it with any of the given mazes
* To run the maze program, execute the server3.exe file in AVC_server folder
* To run the robot program, execute the robot.exe file in AVC_robot folder
