# Free Rotation in 3D

### Description
This project, completed as part of the coursework at the Benemérita Universidad Autónoma de Puebla, focuses on implementing free rotation of a 3D pyramid. The objective is to perform rotations around arbitrary axes using matrix transformations. This enhances understanding of 3D transformations and their applications in computer graphics.

### Overview
Rotations in 3D involve altering the coordinates of an object around a specified axis. This project targets free rotation by calculating unit vectors, applying rotation matrices for each axis, and using inverse matrices for returning to the original position. The implementation uses matrix multiplication to perform the necessary transformations.

### Objectives
- Implement free rotation for a 3D pyramid using matrix transformations in OpenGL.
- Apply learned concepts to rotate the pyramid around any specified axis.
- Develop an understanding of 3D rotations and their applications in computer graphics.

### Key Features
- **Initialization**: Set up the OpenGL environment and window properties.
- **Rotation Functions**: Implement functions for rotating the pyramid around arbitrary axes.
- **Matrix Operations**: Utilize matrix multiplication for applying transformations.
- **Animation Loop**: Continuously apply rotations to animate the 3D pyramid.

### Project Structure
The project includes the following main components:

#### Initialization
This function sets up the OpenGL environment, defining the color of the window and the projection parameters.

```cpp
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.0, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -3.0);
}
```

#### Free Rotation Function

This function handles the free rotation of the pyramid along any specified axis. It first calculates the unit vector and necessary matrices, applies the rotation, and then translates back.

```cpp
void Operaciones3D::RotacionLibre(float theta, float p1[3], float p2[3]) {
    float V, a, b, c, d;

    // Calculate the unit vector
    V = sqrt(pow(p2[0] - p1[0], 2) + pow(p2[1] - p1[1], 2) + pow(p2[2] - p1[2], 2));
    if (V < 0) V = -V;

    a = (p2[0] - p1[0]) / V;
    b = (p2[1] - p1[1]) / V;
    c = (p2[2] - p1[2]) / V;
    d = sqrt(pow(b, 2) + pow(c, 2));

    // Case for the X axis
    if (d == 0) {
        translate(-p1[0], -p1[1], -p1[2]);
        rotateX(DegToRad(theta));
        MultM(R, T, A);
        translate(p1[0], p1[1], p1[2]);
        MultM(T, A, A);
    } else { // For Y and Z axes
        // Translation
        translate(-p1[0], -p1[1], -p1[2]);

        // Calculate RX(alpha)
        LoadIdentity(R);
        R[1][1] = c / d;
        R[1][2] = -b / d;
        R[2][1] = b / d;
        R[2][2] = c / d;
        MultM(T, R, A);

        // Calculate RY(beta)
        LoadIdentity(R);
        R[0][0] = d;
        R[0][2] = a;
        R[2][0] = -a;
        R[2][2] = d;
        MultM(A, R, A);

        // Calculate RZ(theta)
        LoadIdentity(R);
        R[0][0] = cos(DegToRad(theta));
        R[0][1] = -sin(DegToRad(theta));
        R[1][0] = sin(DegToRad(theta));
        R[1][1] = cos(DegToRad(theta));
        MultM(A, R, A);

        // Calculate RY-1(beta)
        LoadIdentity(R);
        R[0][0] = d;
        R[0][2] = -a;
        R[2][0] = a;
        R[2][2] = d;
        MultM(A, R, A);

        // Calculate RX-1(alpha)
        LoadIdentity(R);
        R[1][1] = c / d;
        R[1][2] = b / d;
        R[2][1] = -b / d;
        R[2][2] = c / d;
        MultM(A, R, A);

        // Inverse translation
        translate(p1[0], p1[1], p1[2]);
        MultM(A, T, A);
    }
}
```

#### Translation Function

This function applies a translation to the 3D object by modifying its coordinates.

```cpp
void translate(float dx, float dy, float dz) {
    float T[4][4] = {
        {1, 0, 0, dx},
        {0, 1, 0, dy},
        {0, 0, 1, dz},
        {0, 0, 0, 1}
    };
    MultM(R, T, A);
}
```

#### Rotation Functions

These functions define the rotation matrices for the X, Y, and Z axes and multiply them with the transformation matrix.

```cpp
void rotateX(float theta) {
    float R[4][4] = {
        {1, 0, 0, 0},
        {0, cos(theta), -sin(theta), 0},
        {0, sin(theta), cos(theta), 0},
        {0, 0, 0, 1}
    };
    MultM(T, R, A);
}

void rotateY(float theta) {
    float R[4][4] = {
        {cos(theta), 0, sin(theta), 0},
        {0, 1, 0, 0},
        {-sin(theta), 0, cos(theta), 0},
        {0, 0, 0, 1}
    };
    MultM(T, R, A);
}

void rotateZ(float theta) {
    float R[4][4] = {
        {cos(theta), -sin(theta), 0, 0},
        {sin(theta), cos(theta), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    MultM(T, R, A);
}
```

#### Matrix Multiplication Function

This function multiplies two 4x4 matrices.

```cpp
void MultM(float A[4][4], float B[4][4], float C[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            C[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
```

### Execution

The project initializes a graphical window and applies free rotations to the pyramid along any specified axis. The rotation is continuous, providing a dynamic visual representation of the 3D transformations.

<p align= "center">
    <img src="https://github.com/KPlanisphere/binary-tree-operations/assets/60454942/5f10322a-baae-4521-af6c-f8a60ef142d1" style="width: 70%; height: auto;">
</p>

<p align= "center">
    <img src="https://github.com/KPlanisphere/binary-tree-operations/assets/60454942/5102cd2d-16bf-4c62-b80b-04ad294b192a" style="width: 70%; height: auto;">
</p>
