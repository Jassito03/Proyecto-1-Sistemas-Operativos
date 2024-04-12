<h1 align="center">Proyecto 1 Sistemas Operativos 💻</h1>
<h2>Autores</h2>
<p>Brandon Castillo Badilla <br> Jassdanny Piñar Baltodano</p> 
<h2>¿Cómo utilizar el programa? 🤔</h2>
<p>Para utilizar el programa deberá hacerlo en un ambiente GNU/Linux ⚠.</p>
<ul>
  <li>
    Primeramente clone este repositorio en su computadora. 📥 <br>
    Si no sabe como hacerlo consulte la documentación de GitHub: <a href="https://docs.github.com/es/repositories/creating-and-managing-repositories/cloning-a-repository" target="_blank">Clonar un repositorio</a> ✔. 
  </li>
  <li>Seguidamente ejecute el comando <code>make</code>. ✔</li>
  <li>Luego debe de ingresar su contraseña de súper usuario para instalar el programa. ⚠</li>
  <li>
    Ahora puede utilizar el programa de la siguiente manera: <br>
    <ul>
      <li>
        <code>programa cpu [PID opcional]</code>
        <p>
           &emsp; Al agregar <code>[PID opcional]</code> se mostrará el porcentaje de utilización de CPU para el PID escrito. <br>
        </p> 
      </li>
      <li>
        <code>programa disco [-tm | -tg]</code> <br>
        <p>
          &emsp; Si no se utilizan flags mostrará el porcentaje de uso y libre del disco principal. <br>
          &emsp; La flag <code>-tm</code> mostrará los datos en MiB. <br>
          &emsp; La flag <code>-tg</code> mostrará los datos en GiB. <br>
        </p> 
      </li>
      <li>
        <code>programa memoria [-r | -v] [PID opcional]</code>
        <p>
          &emsp; Si no se utilizan flags mostrará ??. <br>
          &emsp; La flag <code>-r</code> mostrará el porcentaje de memoria real utilizado de cada uno los procesos abiertos. <br>
          &emsp; La flag <code>-v</code> mostrará el porcentaje de memoria virtual utilizado de cada uno los procesos abiertos. <br>
          &emsp; Al agregar <code>[PID opcional]</code> se mostrará el porcentaje de memoria solicitado para el PID escrito. <br>
        </p>
      </li>
    </ul>
  </li>
</ul>
<h2>¿Cómo desinstalar el programa? 🤔</h2>
<p>Si desea desinstalarlo deberá ejecutar el comando <code>make uninstall</code> y proporcionar su contraseña de súper usuario. ✔</p>
