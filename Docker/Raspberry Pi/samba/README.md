# Samba

### Samba en Windows 10
<p> Si vas a utilizar samba en windows 10 (el cual es un poco molesto) deberás habilitar 3 cosas en W10. </p> 
Tutorial: https://youtu.be/bf0wHsiLuuA

### Habilitar Samba en windows 10
   1) Panel de control -> Programas -> Activar o desactivar las características de Windows -> Compatibilidad con el protocolo para compartir archivos SMB 1.0/CIFS
   2) Windows Defender Firewall con seguridad avanzada -> Reglas de entrada -> habilitar TODAS las reglas que comienzan por "Compartir archivos"
   3) Administrar configuración avanzada de uso compartido 
   * Privado -> Activar la detección de redes y Activar el uso compartido de archivos e impresoras
   * Invitado o público (perfil actual) -> Activar la detección de redes y Activar el uso compartido de archivos e impresoras

### Acceder al servidor Samba
   1) Ir a Red, luego hacer click derecho y luego click a "Conectar a unidad de red"
   2) Al estar ahí, simplemente escribes la dirección del servidor, ej: \\192.168.0.10\MEDIA
 
