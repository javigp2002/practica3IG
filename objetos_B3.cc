//**************************************************************************
// Práctica 2
//**************************************************************************

#include "objetos_B3.h"

#include "file_ply_stl.hpp"

//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D() {}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor) {
  int i;
  glPointSize(grosor);
  glColor3f(r, g, b);
  glBegin(GL_POINTS);

  int num_tot_v = vertices.size();
  for (i = 0; i < num_tot_v; i++) {
    glVertex3fv((GLfloat *)&vertices[i]);
  }
  glEnd();

  // // otra manera de hacer lo de arriba
  // glEnableClientState(GL_VERTEX_ARRAY);
  // glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
  // glDrawArrays(GL_POINTS, 0, vertices.size());
}

//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D() {}

//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor) {
  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(grosor);
  glColor3f(r, g, b);
  glBegin(GL_TRIANGLES);

  int num_tot_caras = caras.size();

  for (i = 0; i < num_tot_caras; i++) {
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();

  // //**** usando vertex_array ****
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  // glLineWidth(grosor);
  // glColor3f(r, g, b);

  // glEnableClientState(GL_VERTEX_ARRAY);
  // glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
  // glDrawElements(GL_TRIANGLES, caras.size() * 3, GL_UNSIGNED_INT, &caras[0]);
}

//*************************************************************************
// dibujar en modo sólido con un único color
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b) {
  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(r, g, b);
  glBegin(GL_TRIANGLES);

  int num_tot_caras = caras.size();
  for (i = 0; i < num_tot_caras; i++) {
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}

//*************************************************************************
// dibujar en modo sólido con colores diferentes para cada cara
//*************************************************************************

void _triangulos3D::draw_solido_colores() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);

  int num_tot_caras = caras.size();

  for (int i = 0; i < num_tot_caras; i++) {
    glColor3f(colores_caras[i].r, colores_caras[i].g, colores_caras[i].b);

    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}

//*************************************************************************
// dibujar en modo sólido con colores diferentes para cada vertices
//*************************************************************************

void _triangulos3D::draw_solido_colores_vertices() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);

  int num_tot_caras = caras.size();

  for (int i = 0; i < num_tot_caras; i++) {
    glColor3f(colores_caras[caras[i]._0].r, colores_caras[caras[i]._0].g,
              colores_caras[caras[i]._0].b);

    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);

    glColor3f(colores_caras[caras[i]._1].r, colores_caras[caras[i]._1].g,
              colores_caras[caras[i]._1].b);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);

    glColor3f(colores_caras[caras[i]._2].r, colores_caras[caras[i]._2].g,
              colores_caras[caras[i]._2].b);

    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}
//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r, float g, float b, float grosor) {
  switch (modo) {
    case POINTS:
      draw_puntos(r, g, b, grosor);
      break;
    case EDGES:
      draw_aristas(r, g, b, grosor);
      break;
    case SOLID:
      draw_solido(r, g, b);
      break;
    case SOLID_COLORS:
      draw_solido_colores();
      break;
    case SOLID_COLORS_VERTS:
      draw_solido_colores_vertices();
      break;
  }
}

//*************************************************************************
// asignación colores
//*************************************************************************

void _triangulos3D::colors_random(int caras_iniciales) {
  int i, n_c;
  if (caras_iniciales != -1)
    n_c = caras_iniciales;
  else
    n_c = caras.size();

  colores_caras.resize(n_c);
  srand(time(NULL));
  for (i = 0; i < n_c; i++) {
    colores_caras[i].r = rand() % 1000 / 1000.0;
    colores_caras[i].g = rand() % 1000 / 1000.0;
    colores_caras[i].b = rand() % 1000 / 1000.0;
  }
}

//*************************************************************************
// asignación colores
//*************************************************************************

void _triangulos3D::colors_random_personal() {
  int n_c;
  n_c = caras.size();
  colores_caras.resize(n_c);
  srand(time(NULL));
  for (int i = 0; i < n_c; i++) {
    if (vertices[caras[i]._0].y > 0) {
      colores_caras[i]._0 = rand() % 1000 / 1000.0;
      colores_caras[i]._1 = 0.0;
    } else {
      colores_caras[i]._0 = 0.0;
      colores_caras[i]._1 = rand() % 1000 / 1000.0;
    }

    if (vertices[caras[i]._1].x < 0)
      colores_caras[i]._2 = rand() % 1000 / 1000.0;
    else
      colores_caras[i]._2 = 50.0;
  }
}

//*************************************************************************

void _triangulos3D::colors_chess(float r1, float g1, float b1, float r2,
                                 float g2, float b2) {
  int i, n_c;
  n_c = caras.size();
  colores_caras.resize(n_c);
  for (i = 0; i < n_c; i++) {
    if (i % 2 == 0) {
      colores_caras[i].r = r1;
      colores_caras[i].g = g1;
      colores_caras[i].b = b1;
    } else {
      colores_caras[i].r = r2;
      colores_caras[i].g = g2;
      colores_caras[i].b = b2;
    }
  }
}

//*************************************************************************
// objetos o modelos
//*************************************************************************

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam) {
  // vertices

  float mitad_tam = tam / 2;

  vertices.resize(8);

  vertices[0].x = -mitad_tam;
  vertices[0].y = -mitad_tam;
  vertices[0].z = -mitad_tam;
  vertices[1].x = mitad_tam;
  vertices[1].y = -mitad_tam;
  vertices[1].z = -mitad_tam;
  vertices[2].x = mitad_tam;
  vertices[2].y = -mitad_tam;
  vertices[2].z = mitad_tam;
  vertices[3].x = -mitad_tam;
  vertices[3].y = -mitad_tam;
  vertices[3].z = mitad_tam;
  vertices[4].x = -mitad_tam;
  vertices[4].y = mitad_tam;
  vertices[4].z = -mitad_tam;
  vertices[5].x = mitad_tam;
  vertices[5].y = mitad_tam;
  vertices[5].z = -mitad_tam;
  vertices[6].x = mitad_tam;
  vertices[6].y = mitad_tam;
  vertices[6].z = mitad_tam;
  vertices[7].x = -mitad_tam;
  vertices[7].y = mitad_tam;
  vertices[7].z = mitad_tam;
  // triangulos

  caras.resize(12);
  caras[0]._0 = 3;
  caras[0]._1 = 0;
  caras[0]._2 = 7;
  caras[1]._0 = 0;
  caras[1]._1 = 4;
  caras[1]._2 = 7;
  caras[2]._0 = 0;
  caras[2]._1 = 1;
  caras[2]._2 = 5;
  caras[3]._0 = 0;
  caras[3]._1 = 5;
  caras[3]._2 = 4;
  caras[4]._0 = 1;
  caras[4]._1 = 2;
  caras[4]._2 = 5;
  caras[5]._0 = 2;
  caras[5]._1 = 5;
  caras[5]._2 = 6;
  caras[6]._0 = 2;
  caras[6]._1 = 3;
  caras[6]._2 = 7;
  caras[7]._0 = 2;
  caras[7]._1 = 7;
  caras[7]._2 = 6;
  caras[8]._0 = 0;
  caras[8]._1 = 1;
  caras[8]._2 = 2;
  caras[9]._0 = 0;
  caras[9]._1 = 2;
  caras[9]._2 = 3;
  caras[10]._0 = 4;
  caras[10]._1 = 5;
  caras[10]._2 = 7;
  caras[11]._0 = 5;
  caras[11]._1 = 6;
  caras[11]._2 = 7;

  // colores caras

  colors_random();
}

//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al) {
  // vertices
  vertices.resize(5);
  vertices[0].x = -tam;
  vertices[0].y = 0;
  vertices[0].z = tam;
  vertices[1].x = tam;
  vertices[1].y = 0;
  vertices[1].z = tam;
  vertices[2].x = tam;
  vertices[2].y = 0;
  vertices[2].z = -tam;
  vertices[3].x = -tam;
  vertices[3].y = 0;
  vertices[3].z = -tam;
  vertices[4].x = 0;
  vertices[4].y = al;
  vertices[4].z = 0;

  caras.resize(6);
  caras[0]._0 = 0;
  caras[0]._1 = 1;
  caras[0]._2 = 4;
  caras[1]._0 = 1;
  caras[1]._1 = 2;
  caras[1]._2 = 4;
  caras[2]._0 = 2;
  caras[2]._1 = 3;
  caras[2]._2 = 4;
  caras[3]._0 = 3;
  caras[3]._1 = 0;
  caras[3]._2 = 4;
  caras[4]._0 = 3;
  caras[4]._1 = 1;
  caras[4]._2 = 0;
  caras[5]._0 = 3;
  caras[5]._1 = 2;
  caras[5]._2 = 1;

  colors_random();
}

//*************************************************************************
// clase objeto ply
//*************************************************************************

_objeto_ply::_objeto_ply() {
  // leer lista de coordenadas de vértices y lista de indices de vértices
}

void _objeto_ply::parametros(char *archivo) {
  int n_ver, n_car;

  vector<float> ver_ply;  // xyz se guardan de forma conecutiva
  vector<int> car_ply;

  _file_ply::read(archivo, ver_ply, car_ply);

  n_ver = ver_ply.size() / 3;
  n_car = car_ply.size() / 3;

  printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

  vertices.resize(n_ver);
  caras.resize(n_car);

  // vertices

  for (int i = 0; i < n_ver; i++) {
    vertices[i].x = ver_ply[3 * i];
    vertices[i].y = ver_ply[3 * i + 1];
    vertices[i].z = ver_ply[3 * i + 2];
  }

  // caras

  for (int i = 0; i < n_car; i++) {
    caras[i].x = car_ply[3 * i];
    caras[i].y = car_ply[3 * i + 1];
    caras[i].z = car_ply[3 * i + 2];
  }

  // colores

  colores_caras.resize(n_car);

  colors_random();

  // forma 2
  // colors_random_personal();
}

//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion() {}

void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tipo,
                           int tapa_in, int tapa_su) {
  int i, j;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;
  float radio;

  // tratamiento de los vértice

  if (tipo == 2)
    radio = sqrt(perfil[0].x * perfil[0].x + perfil[0].y * perfil[0].y);
  num_aux = perfil.size();

  int num_tapas = 0;
  if (tipo == 1) num_aux = 1;

  if (tapa_in == 1) num_tapas++;
  if (tapa_su == 1) num_tapas++;
  vertices.resize(num_aux * num + num_tapas);  // +2 pq hemos añadido tapas
  for (j = 0; j < num; j++) {
    for (i = 0; i < num_aux; i++) {
      vertice_aux.x =
          perfil[i].x * cos(2.0 * M_PI * j / (1.0 * num)) +
          perfil[i].z * sin(2.0 * M_PI * j / (1.0 * num));  // 360º en radianes
      vertice_aux.z = -perfil[i].x * sin(2.0 * M_PI * j / (1.0 * num)) +
                      perfil[i].z * cos(2.0 * M_PI * j / (1.0 * num));
      vertice_aux.y = perfil[i].y;
      vertices[i + j * num_aux] = vertice_aux;
    }
  }

  // tratamiento de las caras

  int n_caras =
      (2 * (num_aux - 1) * num + num_tapas * num);  // 2 num pq estan las tapas
  caras.resize(n_caras);
  int c = 0;

  for (int j = 0; j < num; j++) {
    for (int i = 0; i < num_aux - 1; i++) {
      caras[c]._0 = 0 + i + j * num_aux;
      caras[c]._1 = ((j + 1) % num) * num_aux + i;
      caras[c]._2 = 1 + i + j * num_aux;  // el 1 es para enganchar el triangulo

      c++;

      caras[c]._0 = ((j + 1) % num) * num_aux + i;
      caras[c]._1 = ((j + 1) % num) * num_aux + 1 + i;
      caras[c]._2 = 1 + i + j * num_aux;
      c++;
    }
  }

  // tapa inferior

  int total = num_aux * num;

  if (tapa_in == 1) {
    vertices[total].x = 0.0;

    if (tipo == 2)
      vertices[total].y = -radio;
    else
      vertices[total].y = perfil[0].y;

    vertices[total].z = 0.0;

    for (int j = 0; j < num; j++) {
      caras[c]._0 = j * num_aux;
      caras[c]._1 = ((j + 1) % num) * num_aux;
      caras[c]._2 = total;  // el 1 es para enganchar el triangulo

      c++;
    }
  }

  // tapa superior
  if (tapa_su == 1) {
    vertices[total + 1].x = 0.0;
    if (tipo == 1)
      vertices[total + 1].y = perfil[1].y;
    else if (tipo == 0)
      vertices[total + 1].y = perfil[num_aux - 1].y;
    else
      vertices[total + 1].y = radio;
    vertices[total + 1].z = 0.0;

    for (int j = 0; j < num; j++) {
      caras[c]._0 = total + 1;
      caras[c]._1 = ((j + 1) % num) * num_aux + num_aux - 1;
      caras[c]._2 =
          num_aux - 1 + j * num_aux;  // el 1 es para enganchar el triangulo

      c++;
    }
  }

  // colores de las caras
  int n_c = 2 * (num_aux - 1) * num + 2 * num;
  colors_random(n_c);
}

//************************************************************************
//  Rotación PLY
//************************************************************************

_rotacion_PLY::_rotacion_PLY() {}

void _rotacion_PLY::parametros_PLY(char *archivo, int num) {
  int n_ver;
  vector<float> ver_ply;
  vector<int> car_ply;
  vector<_vertex3f> perfil;

  _vertex3f aux;

  _file_ply::read(archivo, ver_ply, car_ply);

  n_ver = ver_ply.size() / 3;

  printf("Number of vertices=%d", n_ver);

  vertices.resize(n_ver);

  // vertices

  for (int i = 0; i < n_ver; i++) {
    aux.x = ver_ply[3 * i];
    aux.y = ver_ply[3 * i + 1];
    aux.z = ver_ply[3 * i + 2];
    perfil.push_back(aux);
  }

  parametros(perfil, num, 0, 1, 0);
}
//************************************************************************
// objeto por extrusión
//************************************************************************

_extrusion::_extrusion(vector<_vertex3f> poligono, float x, float y, float z) {
  int i;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;

  // tratamiento de los vértice

  num_aux = poligono.size();
  vertices.resize(num_aux * 2);
  for (i = 0; i < num_aux; i++) {
    vertices[2 * i] = poligono[i];
    vertices[2 * i + 1].x = poligono[i].x + x;
    vertices[2 * i + 1].y = poligono[i].y + y;
    vertices[2 * i + 1].z = poligono[i].z + z;
  }

  // tratamiento de las caras

  caras.resize(num_aux * 2);
  int c = 0;
  for (i = 0; i < num_aux; i++) {
    caras[c]._0 = i * 2;
    caras[c]._1 = (i * 2 + 2) % (num_aux * 2);
    caras[c]._2 = i * 2 + 1;
    c = c + 1;
    caras[c]._0 = (i * 2 + 2) % (num_aux * 2);
    caras[c]._1 = (i * 2 + 2) % (num_aux * 2) + 1;
    caras[c]._2 = i * 2 + 1;
    c = c + 1;
  }

  // colores de las caras
  colors_random();
}

//************************************************************************

_cilindro::_cilindro(float radio, float altura, int num, int tapa_in,
                     int tapa_su) {
  vector<_vertex3f> perfil;
  _vertex3f vert_aux;

  vert_aux.x = radio;
  vert_aux.y = -altura / 2.0;
  vert_aux.z = 0.0;
  perfil.push_back(vert_aux);

  vert_aux.x = radio;
  vert_aux.y = altura / 2.0;
  vert_aux.z = 0.0;
  perfil.push_back(vert_aux);

  parametros(perfil, num, 0, tapa_in, tapa_su);
}

//************************************************************************
_cono::_cono(float radio, float altura, int num) {
  vector<_vertex3f> perfil;
  _vertex3f vert_aux;

  vert_aux.x = radio;
  vert_aux.y = 0.0;
  vert_aux.z = 0.0;
  perfil.push_back(vert_aux);

  vert_aux.x = 0;
  vert_aux.y = altura;
  vert_aux.z = 0.0;
  perfil.push_back(vert_aux);

  parametros(perfil, num, 1, 1, 1);
}

//************************************************************************

_esfera::_esfera(float radio, int num1, int num2) {
  vector<_vertex3f> perfil;
  _vertex3f vert_aux;

  for (int i = 1; i < num1; i++) {
    vert_aux.x = radio * cos(M_PI * i / num1 -
                             M_PI / 2.0);  // - pq empezamos a girar desde
    vert_aux.y = radio * sin(M_PI * i / num1 - M_PI / 2.0);
    vert_aux.z = 0.0;
    perfil.push_back(vert_aux);
  }

  parametros(perfil, num2, 2, 1, 1);
}

//************************************************************************
// práctica 3, objeto jerárquico articulado
//************************************************************************

//************************************************************************
// piezas
//************************************************************************
//************************************************************************
// pala
//************************************************************************

_pala::_pala(float radio, float ancho, int num) {
  vector<_vertex3f> perfil;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int i, j;

  vertice_aux.x = radio;
  vertice_aux.y = 0;
  vertice_aux.z = -ancho / 2.0;
  perfil.push_back(vertice_aux);
  vertice_aux.z = ancho / 2.0;
  perfil.push_back(vertice_aux);

  // tratamiento de los vértices

  for (j = 0; j <= num; j++) {
    for (i = 0; i < 2; i++) {
      vertice_aux.x = perfil[i].x * cos(M_PI * j / (1.0 * num)) -
                      perfil[i].y * sin(M_PI * j / (1.0 * num));
      vertice_aux.y = perfil[i].x * sin(M_PI * j / (1.0 * num)) +
                      perfil[i].y * cos(M_PI * j / (1.0 * num));
      vertice_aux.z = perfil[i].z;
      vertices.push_back(vertice_aux);
    }
  }

  // tratamiento de las caras

  for (j = 0; j < num; j++) {
    cara_aux._0 = j * 2;
    cara_aux._1 = (j + 1) * 2;
    cara_aux._2 = (j + 1) * 2 + 1;
    caras.push_back(cara_aux);

    cara_aux._0 = j * 2;
    cara_aux._1 = (j + 1) * 2 + 1;
    cara_aux._2 = j * 2 + 1;
    caras.push_back(cara_aux);
  }

  // tapa inferior
  vertice_aux.x = 0;
  vertice_aux.y = 0;
  vertice_aux.z = -ancho / 2.0;
  vertices.push_back(vertice_aux);

  for (j = 0; j < num; j++) {
    cara_aux._0 = j * 2;
    cara_aux._1 = (j + 1) * 2;
    cara_aux._2 = vertices.size() - 1;
    caras.push_back(cara_aux);
  }

  // tapa superior
  vertice_aux.x = 0;
  vertice_aux.y = 0;
  vertice_aux.z = ancho / 2.0;
  vertices.push_back(vertice_aux);

  for (j = 0; j < num; j++) {
    cara_aux._0 = j * 2 + 1;
    cara_aux._1 = (j + 1) * 2 + 1;
    cara_aux._2 = vertices.size() - 1;
    caras.push_back(cara_aux);
  }

  colors_chess(1.0, 1.0, 0.0, 0.0, 0.0, 1.0);
}

//************************************************************************
// brazo
//************************************************************************

_brazo::_brazo() {
  ancho = 0.6;
  alto = 0.1;
  fondo = 0.1;
  colors_chess(1.0, 1.0, 0.0, 0.0, 0.0, 1.0);
};

void _brazo::draw(_modo modo, float r, float g, float b, float grosor) {
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  glTranslatef(0.5, 0, 0);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

//************************************************************************
// cabina
//************************************************************************

_cabina::_cabina() {
  ancho = 0.4;
  alto = 0.6;
  fondo = 0.4;
  cubo.colors_chess(1.0, 1.0, 0.0, 0.0, 0.0, 1.0);
};

void _cabina::draw(_modo modo, float r, float g, float b, float grosor) {
  glPushMatrix();
  glScalef(ancho / 2, alto, fondo);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

//************************************************************************
// sustentación
//************************************************************************

_sustentacion::_sustentacion() {
  ancho = 1.2;
  alto = 0.3;
  fondo = 0.8;
  radio = 0.15;
  base.colors_chess(1.0, 1.0, 0.0, 0.0, 0.0, 1.0);
};

void _sustentacion::draw(_modo modo, float r, float g, float b, float grosor) {
  glPushMatrix();
  glTranslatef(2 * ancho / 6, -alto / 2.0, 0);
  glRotatef(90, 1, 0, 0);
  glScalef(radio, fondo / 2.2, radio);
  rueda.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-2 * ancho / 6, -alto / 2.0, 0);
  glRotatef(90, 1, 0, 0);
  glScalef(radio, fondo / 2.2, radio);
  rueda.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(ancho, alto, fondo);
  base.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

//************************************************************************
// excavadora (montaje del objeto final)
//************************************************************************

_excavadora::_excavadora() {
  giro_cabina = 0.0;
  giro_primer_brazo = 0.0;
  giro_primer_brazo_max = 0;
  giro_primer_brazo_min = -90;
  giro_segundo_brazo = 0.0;
  giro_segundo_brazo_max = 30;
  giro_segundo_brazo_min = 0;
  giro_pala = 0.0;
  giro_pala_max = 50.0;
  giro_pala_min = -90.0;

  tamanio_pala = 0.15;
};

void _excavadora::draw(_modo modo, float r, float g, float b, float grosor) {
  glPushMatrix();

  sustentacion.draw(modo, r, g, b, grosor);

  glTranslatef(0, (cabina.alto + sustentacion.alto) / 2.0, 0);
  glRotatef(giro_cabina, 0, 1, 0);
  cabina.draw(modo, r, g, b, grosor);

  glTranslatef(cabina.ancho / 2.0, 0, 0);
  glRotatef(giro_segundo_brazo, 0, 0, 1);
  brazo.draw(modo, r, g, b, grosor);

  glTranslatef(brazo.ancho, 0, 0);
  glRotatef(giro_primer_brazo, 0, 0, 1);
  brazo.draw(modo, r, g, b, grosor);

  glTranslatef(brazo.ancho, 0, 0);
  glRotatef(giro_pala, 0, 0, 1);
  glTranslatef(tamanio_pala, 0, 0);
  glScalef(tamanio_pala, tamanio_pala, tamanio_pala);
  pala.draw(modo, r, g, b, grosor);

  glPopMatrix();
};

//************************************************************************
// piezas AMETRALLADORA
//************************************************************************

//************************************************************************
// cañon
//************************************************************************

_canon::_canon() {
  ancho = an;
  fondo = f;
  radio = r;
  alto = al;

    cilindro = _cilindro(RADIOCILINDRO, ALTURACILINDRO, 20, 0, 0);
  canonSmall = _cilindro(RADIOCILINDRO, ALTURACILINDRO, 20, 0, 0);

  cilindro.colors_chess(0.35, 0.35, 0.35, 0.45, 0.45, 0.45);
  canonSmall.colors_chess(0.35, 0.35, 0.35, 0.45, 0.45, 0.45);
  rotationModule.colors_chess(0.15, 0.15, 0.15, 0.1, 0.1, 0.1);
  embellecedor.colors_chess(0.15, 0.15, 0.15, 0.1, 0.1, 0.1);
}

void _canon::draw(_modo modo, float r, float g, float b, float grosor) {
  float altoCilindros = alto / 2;
  float transZCilindros = alto / 2.0;
  float radio_medium = radio / 8;

  float radioCanonChico = (radio / 8) / 3;
  float altoCanonChico = alto;

  float transZCanonGrande = altoCanonChico / 2 + altoCilindros / 2;

  glPushMatrix();
  glTranslatef(0, 0, transZCanonGrande);
  glScalef(radio_medium, radio_medium, altoCilindros);
  glRotatef(90, 1, 0, 0);
  cilindro.draw(modo, r, g, b, grosor);
  glPopMatrix();

  float radioEmbellecedores = radio / 3;
  float altoModsPequenos = alto / 64;
  float transZEmbellecedor =
      transZCanonGrande - (altoCilindros * ALTURACILINDRO) / 2;

  // embellecedores
  float altoEmbellecedorGrande = altoModsPequenos * 3;

  introduceEmbellecedor(0, 0, transZEmbellecedor, radioEmbellecedores,
                        altoEmbellecedorGrande, modo, r, g, b, grosor);

  float transZEmbellecedorInter =
      transZEmbellecedor + (altoCilindros * ALTURACILINDRO) / 2;
  introduceEmbellecedor(0, 0, transZEmbellecedorInter, radioEmbellecedores,
                        altoModsPequenos, modo, r, g, b, grosor);

  transZEmbellecedorInter +=
      transZEmbellecedor + (altoCilindros * ALTURACILINDRO) / 3;
  introduceEmbellecedor(0, 0, transZEmbellecedorInter, radioEmbellecedores,
                        altoModsPequenos, modo, r, g, b, grosor);

  transZEmbellecedor = transZCanonGrande + altoCilindros * ALTURACILINDRO / 2 -
                       altoModsPequenos * ALTURACILINDRO;
  introduceEmbellecedor(0, 0, transZEmbellecedor, radioEmbellecedores,
                        altoModsPequenos, modo, r, g, b, grosor);

  float final = 3 * radio / 4, intermedio = radio / 2;
  introduceSmallCanon(final, 0, 0, modo, radioCanonChico, altoCanonChico, r, g,
                      b, grosor);
  introduceSmallCanon(-final, 0, 0, modo, radioCanonChico, altoCanonChico, r, g,
                      b, grosor);

  introduceSmallCanon(-intermedio, intermedio, 0, modo, radioCanonChico,
                      altoCanonChico, r, g, b, grosor);
  introduceSmallCanon(intermedio, intermedio, 0, modo, radioCanonChico,
                      altoCanonChico, r, g, b, grosor);

  introduceSmallCanon(0, final, 0, modo, radioCanonChico, altoCanonChico, r, g,
                      b, grosor);
  introduceSmallCanon(0, -final, 0, modo, radioCanonChico, altoCanonChico, r, g,
                      b, grosor);

  introduceSmallCanon(-intermedio, -intermedio, 0, modo, radioCanonChico,
                      altoCanonChico, r, g, b, grosor);
  introduceSmallCanon(intermedio, -intermedio, 0, modo, radioCanonChico,
                      altoCanonChico, r, g, b, grosor);

  float transRMZ = -altoCanonChico * ALTURACILINDRO / 2;
  float altoRM = altoEmbellecedorGrande;

  introduceRotationModule(0, 0, transRMZ, radioEmbellecedores, altoRM, modo, r,
                          g, b, grosor);
}

void _canon::introduceSmallCanon(float posX, float posY, float posZ, _modo modo,
                                 float radio, float alto, float r, float g,
                                 float b, float grosor) {
  // canon
  glPushMatrix();
  glTranslatef(posX, posY, posZ);
  glScalef(radio, radio, alto);
  glRotatef(90, 1, 0, 0);

  canonSmall.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

void _canon::introduceEmbellecedor(float posX, float posY, float posZ,
                                   float radio, float alto, _modo modo, float r,
                                   float g, float b, float grosor) {
  glPushMatrix();
  glTranslatef(posX, posY, posZ);  // transladar de manera que quede bien
  glScalef(radio, radio, alto);
  glRotatef(90, 1, 0, 0);
  embellecedor.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

void _canon::introduceRotationModule(float posX, float posY, float posZ,
                                     float radio, float alto, _modo modo,
                                     float r, float g, float b, float grosor) {
  glPushMatrix();
  glTranslatef(posX, posY, posZ);  // transladar de manera que quede bien
  glScalef(radio, radio, alto);
  glRotatef(90, 1, 0, 0);
  rotationModule.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

//************************************************************************
// cargador
//************************************************************************
// float an = 1;
// float al = 1.5;
// float f = 1;
// float r = 0.45;
_cargador::_cargador() {
  ancho = 1;
  fondo = 1;
  radio = 0.45;
  alto = 1.5;

  // cubo.colors_chess(0.55, 0.55, 0.55, 0.5, 0.5, 0.5);
  cubo.colors_chess(0.18, 0.26, 0.13, 0.2, 0.1, 0.11);
}

void _cargador::draw(_modo modo, float r, float g, float b, float grosor) {
  // base Cargador
  float altoBaseCargador = 1;
  float fondoBaseCargador = 0.25;
  float anchoBaseCargador = 1;

  introduceEmbellecedor(0, 0, 0, anchoBaseCargador, altoBaseCargador,
                        fondoBaseCargador, modo, r, g, b, grosor);

  // base Union Cargador
  float altoBaseUnionCargador = 0.1;
  float fondoBaseUnionCargador = 0.2;
  float anchoBaseUnionCargador = 0.8;
  float transXBaseUnionCargador = anchoBaseCargador/2;
  float transYBaseUnionCargador = altoBaseCargador/2+0.05;
  float transZBaseUnionCargador = 0;

  glPushMatrix();
  glTranslatef(transXBaseUnionCargador, transYBaseUnionCargador,
               transZBaseUnionCargador);
  glRotatef(10, 0, 0, 1);
  glScalef(anchoBaseUnionCargador, altoBaseUnionCargador,
           fondoBaseUnionCargador);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

void _cargador::introduceEmbellecedor(float posX, float posY, float posZ,
                                     float ancho, float alto, float fondo,
                                     _modo modo, float r, float g, float b,
                                     float grosor) {
  glPushMatrix();
  glTranslatef(posX, posY, posZ);
  glScalef(ancho, alto, fondo);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

//************************************************************************
// housing
//************************************************************************
// float an = 1;
// float al = 1.5;
// float f = 1;
// float r = 0.45;
_housing::_housing() {
  ancho = 1;
  fondo = 1;
  radio = 0.45;
  alto = 1.5;

  // cilindro.colors_chess(0.35, 0.35, 0.35, 0.3, 0.3, 0.3);
  // cubo.colors_chess(0.35, 0.35, 0.35, 0.3, 0.3, 0.3);
  // cono.colors_chess(0.35, 0.35, 0.35, 0.3, 0.3, 0.3);

  

  cilindro.colors_chess(0.18, 0.26, 0.13, 0.2, 0.1, 0.11);
  cubo.colors_chess(0.18, 0.26, 0.13, 0.2, 0.1, 0.11);
  cono.colors_chess(0.18, 0.26, 0.13, 0.2, 0.1, 0.11);
}

void _housing::draw(_modo modo, float r, float g, float b, float grosor,
                    float giro_mira) {
  // // Todos estos vienen "heredados del cañon"

  float altoEmbCanion = alto / 48;
  float radioEmbCanion = radio / 3;
  // float transembellecedor = -2.1 * alto;

  float altoB = altoEmbCanion + 0.5;
  float radioB = radioEmbCanion + 0.02;

  // base
  introduceRotationModule(0, 0, 0, radioB, altoB, modo, r, g, b, grosor);

  // trasera base

  float altoBAtras = al / 64;
  float transZBAtras =
      -(altoB * ALTURACILINDRO) / 2.0 - (altoBAtras * ALTURACILINDRO) / 2;

  introduceRotationModule(0, 0, transZBAtras, radioEmbCanion, altoBAtras, modo,
                          r, g, b, grosor);

  // cono embellecedor
  float alturaCono = 3;
  float transXCono = 0;
  float transYCono = 0;
  float altoCono = altoBAtras * 3;
  float transZCono = transZBAtras - (altoBAtras * ALTURACILINDRO) / 2;
  float radioCono = radioEmbCanion;

  glPushMatrix();
  glTranslatef(transXCono, transYCono,
               transZCono);  // transladar de manera que quede bien
  glScalef(radioCono, radioCono, altoCono);
  glRotatef(270, 1, 0, 0);
  cono.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // embellecedor palo
  float transXPaloEmb = transXCono;
  float transYPaloEmb = transYCono;
  float altoPaloEmb = alto / 8;
  float transZPaloEmb = transZCono - (altoCono * alturaCono) / 2 -
                        (altoPaloEmb * ALTURACILINDRO) / 2;
  float radioPaloEmb = radioB / 6;

  introduceRotationModule(transXPaloEmb, transYPaloEmb, transZPaloEmb,
                          radioPaloEmb, altoPaloEmb, modo, r, g, b, grosor);

  // tubo cargador

  float transXTuboExt = -(3 * (radioB * (RADIOCILINDRO * 2) / 2) / 4.0);
  float transYTuboExt = transXTuboExt;
  float transZTuboExt = -(altoB * ALTURACILINDRO) / 3.5;
  float radioTuboExt = radioB / 2.5;
  float altoTuboExt = alto / 3.5;

  introduceRotationModule(transXTuboExt, transYTuboExt, transZTuboExt,
                          radioTuboExt, altoTuboExt, modo, r, g, b, grosor);

  // trasera tubo cargador
  float transXTuboExtAtras = transXTuboExt;
  float transYTuboExtAtras = transYTuboExt;
  float altoTuboExtAtras = alto / 24;
  float transZTuboExtAtras = transZTuboExt -
                             (altoTuboExt * ALTURACILINDRO) / 2.0 -
                             (altoTuboExtAtras * ALTURACILINDRO) / 2.0;
  float radioTuboExtAtras = radioTuboExt - 0.02;

  introduceRotationModule(transXTuboExtAtras, transYTuboExtAtras,
                          transZTuboExtAtras, radioTuboExtAtras,
                          altoTuboExtAtras, modo, r, g, b, grosor);

 
  float escalaCargador = 0.7;
   //cargador
  glPushMatrix();
  glTranslatef(2.5*transXTuboExt, 2*transYTuboExt, transZTuboExt);
  glScalef(escalaCargador,escalaCargador,2*escalaCargador);
  cargador.draw(modo,r,g,b,grosor);
  glPopMatrix();
  // base mango
  float altoBaseMango = alto / 20;
  float fondoBaseMango = alto / 5;
  float transXBaseMango = 0;
  float anchoBaseMango = 1.5 * (radioB * 2 * RADIOCILINDRO);
  float transYBaseMango = (radioB * RADIOCILINDRO) + altoBaseMango / 2 -
                          0.02;  // el cubo tiene tam 1 por def
  float transZBaseMango = (altoB * ALTURACILINDRO) / 2 - fondoBaseMango;

  introduceEmbellecedor(transXBaseMango, transYBaseMango, transZBaseMango,
                        anchoBaseMango, altoBaseMango, fondoBaseMango, modo, r,
                        g, b, grosor);

  // partes mango
  float transYMira =
      transYBaseMango + altoBaseMango / 2 + 0.02;  // 0.5 del alto mirilla
  float transZMira = transZBaseMango;  // arreglar aqui la mira q funcione bn

  float transYMirilla = 1;  // alto mirilla
  float escala = 0.5;
  glPushMatrix();

  glTranslatef(0, transYMira, transZMira);  // pos final
  glScalef(escala, escala, escala);
  glRotatef(giro_mira, 1, 0, 0);      // rotacion
  glTranslatef(0, transYMirilla, 0);  // mover punto del medio
  mira.draw(modo, r, g, b, grosor);
  glPopMatrix();


 
}

void _housing::introduceAgarre(float posX, float posY, float posZ, float radio,
                               float alto, _modo modo, float r, float g,
                               float b, float grosor, bool rotate) {
  glPushMatrix();

  glTranslatef(posX, posY, posZ);  // transladar de manera que quede bien

  if (rotate) glRotatef(90, 1, 0, 0);
  cilindro.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

void _housing::introduceRotationModule(float posX, float posY, float posZ,
                                       float radio, float alto, _modo modo,
                                       float r, float g, float b, float grosor,
                                       bool rotate) {
  glPushMatrix();

  glTranslatef(posX, posY, posZ);  // transladar de manera que quede bien
  glScalef(radio, radio, alto);
  if (rotate) glRotatef(90, 1, 0, 0);
  cilindro.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

void _housing::introduceEmbellecedor(float posX, float posY, float posZ,
                                     float ancho, float alto, float fondo,
                                     _modo modo, float r, float g, float b,
                                     float grosor) {
  glPushMatrix();
  glTranslatef(posX, posY, posZ);
  glScalef(ancho, alto, fondo);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

//************************************************************************
// Mirilla
//************************************************************************

_mirilla::_mirilla() {
  ancho = an;
  fondo = f;
  radio = r;
  alto = al;

  campana = _cilindro(RADIOCILINDRO, ALTURACILINDRO, 30, 0, 0);
  modRot = _cilindro(RADIOCILINDRO, ALTURACILINDRO, 30, 1, 1);

  campana.colors_chess(0.7, 0.7, 0.7, 0.6, 0.6, 0.6);
  modRot.colors_chess(0.5, 0.5, 0.5, 0.6, 0.6, 0.6);
  mira.colors_chess(0.3, 0.3, 0.3, 0.4, 0.4, 0.4);
}

void _mirilla::introduceMira(float posX, float posY, float posZ, float ancho,
                             float alto, float fondo, _modo modo, float r,
                             float g, float b, float grosor, bool rotate) {
  glPushMatrix();
  glTranslatef(posX, posY, posZ);  // transladar de manera que quede bien
  glScalef(ancho, alto, fondo);
  if (rotate) glRotatef(90, 1, 0, 0);
  mira.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

void _mirilla::introduceBase(float posX, float posY, float posZ, float ancho,
                             float alto, float fondo, _modo modo, float r,
                             float g, float b, float grosor, bool rotate) {
  introduceMira(posX, posY, posZ, ancho, alto, fondo, modo, r, g, b, grosor,
                rotate);
}

void _mirilla::introduceCampana(float posX, float posY, float posZ, float radio,
                                float alto, _modo modo, float r, float g,
                                float b, float grosor, bool rotate) {
  glPushMatrix();
  glTranslatef(posX, posY, posZ);
  glScalef(radio, radio, alto);
  if (rotate) glRotatef(90, 1, 0, 0);
  campana.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

void _mirilla::draw(_modo modo, float r, float g, float b, float grosor) {
  float anchoMirilla = 0.02, altoMirilla = 1, fondoMirilla = anchoMirilla;

  introduceMira(0, 0, 0, anchoMirilla, altoMirilla, fondoMirilla, modo, r, g, b,
                grosor, false);

  introduceMira(0, 0, 0, altoMirilla, anchoMirilla, fondoMirilla, modo, r, g, b,
                false);

  float radioMirilla = (altoMirilla / 2) / RADIOCILINDRO;
  introduceCampana(0, 0, 0, radioMirilla, fondoMirilla, modo, r, g, b, grosor,
                   true);

  float altoBase = altoMirilla / 2;
  float transYBase = -altoMirilla / 2 - altoBase / 2;
  introduceBase(0, transYBase, 0, anchoMirilla * 2, altoBase, 2 * fondoMirilla,
                modo, r, g, b, grosor, false);

  float altoModR = anchoMirilla * 2;
  float radioModR = fondoMirilla;
  float transYModR = transYBase - (altoBase) / 2;
  introduceModRotatorio(0, transYModR, 0, radioModR * 2, altoModR, modo, r, g,
                        b, grosor, true);
}

void _mirilla::introduceModRotatorio(float posX, float posY, float posZ,
                                     float radio, float alto, _modo modo,
                                     float r, float g, float b, float grosor,
                                     bool rotate) {
  glPushMatrix();
  glTranslatef(posX, posY, posZ);  // transladar de manera que quede bien
  glScalef(radio, radio, alto);
  if (rotate) glRotatef(90, 1, 0, 0);
  if (rotate) glRotatef(90, 0, 0, 1);
  modRot.draw(modo, r, g, b, grosor);
  glPopMatrix();
}
//************************************************************************
// sustentación
//************************************************************************

_sustentacionAmetralladora::_sustentacionAmetralladora() {
  ancho = 1;
  alto = 0.2;
  fondo = 1;

  base.colors_chess(0.18, 0.26, 0.13, 0.2, 0.1, 0.11);
  pataIzda.colors_chess(0.18, 0.26, 0.13, 0.2, 0.1, 0.11);
  pataDcha.colors_chess(0.18, 0.26, 0.13, 0.2, 0.1, 0.11);
  pataAtras.colors_chess(0.18, 0.26, 0.13, 0.2, 0.1, 0.11);
  baseIzda.colors_chess(0.18, 0.26, 0.13, 0.2, 0.1, 0.11);
  baseAtras.colors_chess(0.18, 0.26, 0.13, 0.2, 0.1, 0.11);
  paloBase.colors_chess(0.18, 0.26, 0.13, 0.2, 0.1, 0.11);
};

void _sustentacionAmetralladora::draw(_modo modo, float r, float g, float b,
                                      float grosor) {
  // base
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  base.draw(modo, r, g, b, grosor);
  glPopMatrix();

  float transX = 3 * ancho / 2;
  float transY = alto / 3.0;

  // izda
  glPushMatrix();
  glTranslatef(transX, transY, 0);
  glScalef(ancho * 2, alto / 3.0, fondo / 3.0);
  pataIzda.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // dcha
  glPushMatrix();
  glTranslatef(-transX, transY, 0);
  glScalef(ancho * 2, alto / 3.0, fondo / 3.0);
  pataIzda.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // atras
  glPushMatrix();
  glTranslatef(0.0, transY, -transX);
  glScalef(fondo / 3.0, alto / 3.0, ancho * 2);
  pataAtras.draw(modo, r, g, b, grosor);
  glPopMatrix();

  float transXApoyo = 10 * ancho / 4.0;
  float transYApoyo = alto / 6.0;

  // izda apoyo
  glPushMatrix();
  glTranslatef(transXApoyo, -transYApoyo, 0);
  glScalef(ancho / 4, 2 * alto / 3.0, fondo / 3.0);
  baseIzda.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // // dcha apoyo
  glPushMatrix();
  glTranslatef(-transXApoyo, -transYApoyo, 0);
  glScalef(ancho / 4, 2 * alto / 3.0, fondo / 3.0);
  baseDcha.draw(modo, r, g, b, grosor);
  glPopMatrix();
  // // atras apoyo
  glPushMatrix();
  glTranslatef(0, -transYApoyo, -transXApoyo);
  glScalef(ancho / 4, 2 * alto / 3.0, fondo / 3.0);
  baseAtras.draw(modo, r, g, b, grosor);
  glPopMatrix();

  float alturaPalo = 16;
  float anchuraPalo = 0.7;
  float scaleAncho = anchuraPalo * ancho, scaleFondo = anchuraPalo * fondo;

  float transYPalo = (alturaPalo / 2.0 ) * alto;

  // //palo base4A
  glPushMatrix();
  glTranslatef(0, transYPalo * 2, 0);  //+0.5 para q empiece encima de la base
  glScalef(scaleAncho / 2.0, alturaPalo * alto * 2, scaleFondo / 2.0);
  baseAtras.draw(modo, r, g, b, grosor);
  glPopMatrix();



};

//************************************************************************
// excavadora (montaje del objeto final)
//************************************************************************

_ametralladora::_ametralladora() {
  giro_canion = 0.0;
  giro_base = 0.0;
  giro_base_up = 0.0;

  giro_base_max = 90;
  giro_base_min = -90;

  giro_base_up_max = 30;
  giro_base_up_min = -30;

  giro_mirilla = -90;
  giro_mirilla_min = -90.0;
  giro_mirilla_max = 0.0;

  tamanio_pala = 0.15;
};

void _ametralladora::draw(_modo modo, float r, float g, float b, float grosor) {
  glPushMatrix();
  float ajusteScale = 0.5;
  glScalef(ajusteScale, ajusteScale, ajusteScale);
  glTranslatef(0, -7.1, 0);

  sustentacion.draw(modo, r, g, b, grosor);

  glPopMatrix();

  glPushMatrix();

  float rotacionX = (giro_base_max - abs(giro_base)) / giro_base_max;
  float rotacionZ = 1 - rotacionX;

  if (giro_base > 0) rotacionZ *= -1;
  glRotatef(giro_base_up, rotacionX, 0, rotacionZ);
  glRotatef(giro_base, 0, 1, 0);
  housing.draw(modo, r, g, b, grosor, giro_mirilla);

  glTranslatef(0, 0, 3);
  glRotatef(giro_canion, 0, 0, 1);

  canon.draw(modo, r, g, b, grosor);

  glPopMatrix();

  // glPushMatrix();

  // // glRotatef(giro_base, 1, 0, 0);
  // // glRotatef(giro_base_up, 0, 1, 0);
  // housing.draw(modo, r, g, b, grosor);

  // glPopMatrix();
};
